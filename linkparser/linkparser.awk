BEGIN {
	version = "0.3.1"
	printf("link-parser, v%s\n", version)

	true = 1
	false = 0
	g_srcroot = ""
	g_instroot = ""
	tar_root = ""

	# Colors
	RED="\033[0;31m"
	GRN="\033[0;32m"
	BLU="\033[0;34m"
	NC="\033[0m"
	BOL="\033[1m"

	count = 0

	if (arg ~ /ut/) {
		do_test();
		SKIP_END = true
		exit 0
	}

	if (arg ~ /pretend/) {
		pretend = true
	}

	if (arg ~ /dest=/) {
		destdir = gensub(/^.+dest=([^ \t;,]+)/, "\\1", "g", arg)
		if (system("test -d " destdir) != 0) {
			print "Directory [" destdir "] doesn't exist!"
			SKIP_END = true
			exit 0
		}
	}

	# Get g_srcroot
	getline line
	get_g_srcroot(line)
	printf("Parsing and dumping, this may take for a while...\n")
}

/^[^-]/ {
	# A link is a file name suffixed with '.o', '.lib' or '.obj' in a line.
	link = $0
	# Remove the ending ' \'
	gsub(/[ \t]+\\$/, "", link)

	# Parse .cmd files
	cmd_file = link".cmd"
	parse_cmd(cmd_file)
}

function get_g_srcroot(line) {
	if (g_srcroot)
		return

	patt = "\\/sw\\/vobs.+"
	if (line !~ patt)
		return

	gsub(patt, "", line)
	patt = ".+\\/"
	gsub(patt, "", line)
	g_srcroot = line
	"date +%Y%m%d-%H%M%S" | getline date
	g_instroot = g_srcroot"-"date

	if (destdir)
		g_instroot = destdir"/"g_instroot
}

function parse_cmd(cmd) {
	while ((getline line < cmd) > 0) {
		# Get dependence file, in the argument of option '-Wp,-MD'
		patt = "cd (.+);.+-MD,([^ \t]+)\\.d.+"
		if (line ~ patt) {
			dep = gensub(patt, "\\1/\\2.D", "g", line)
			# Parsing dependence file
			parse_dep(dep)
		} else if (pretend) {
			print RED line NC
		}

		# Get source file, suffixed with '.c', '.cpp', or '.cc'
		# ...

		# abosolute path
		if (line ~ /[ \t]+-c[ \t]+\/.+$/)
			source = gensub(/^.+[ \t]+-c[ \t]+(.+)$/, "\\1", "g", line)
		else # relative path
			source = gensub(/^cd (.+);.+-c (.+)/, "\\1/\\2", "g", line)

		# path transform
		#patt = "vobs\\/esam\\/objects\\/([^\\/]+\\/){2,2}sources\\/"
		patt = "vobs\\/esam\\/objects\\/.+\\/sources\\/(flat|src)"
		gsub(patt, "vobs/dsl/sw/flat", source)

		patt = "vobs\\/esam\\/objects\\/.+\\/sources\\/itf"
		gsub(patt, "vobs/dsl/sw/itf", source)

		patt = "\\/esam\\/.+\\/dummy\\.c"
		if (source ~ patt)
			continue;

		rel_install(source, g_srcroot, g_instroot)
	}
	close(cmd)
}

function parse_dep(dep) {
	# Get path prefix
	if ((getline < dep) < 0)
		return
	cur_path = $1
	gsub(/^#/, "", cur_path)

	while ((getline < dep) > 0) {
		gsub(/.+:/, " ")
		for (i = 1; i <= NF; i++) {
			#if ($i !~ /\.(h|hpp)$/)
			#	continue
			if ($i == "\\") continue

			header = cur_path "/" $i
			if (!buildroot_host_path) {
				patt = "(.+\\/esam\\/.+\\/output\\/host)\\/.+$"
				if (header ~ patt) {
					buildroot_host_path = gensub(patt, "\\1", "g", header)

					patt = ".+\\/"g_srcroot"\\/sw\\/vobs"
					gsub(patt, g_instroot"/sw/vobs", buildroot_host_path)
				}
			}

			rel_install(header, g_srcroot, g_instroot)
		}
	}
	close(dep)
}

END {
	if (SKIP_END)
		exit 0
	print "Total dumped files: " count

	if (buildroot_host_path && arg !~ /pretend/)
		system("mv " buildroot_host_path " " g_instroot"/sw/")

	if (arg ~ /tar/)
		make_tarball(arg)
}

function rel_install(source, rel_root, new_root) {
	count++
	
	dir = dirname(source)
	base = basename(source)
	patt = "^.+\\/"rel_root"\\/(sw.+)"
	rel_path = gensub(patt, "\\1", "g", dir)

	if (pretend) {
		print source > rel_root".source.list"
		print rel_path"/"base > rel_root".relative.list"
		return 0
	}

	system("mkdir -p " new_root "/" rel_path)

	cmdline = "if test -e " new_root "/" rel_path "/" base \
		";then echo yes;else echo no;fi"
	cmdline |getline ret
	close(cmdline)
	if (ret == "yes") {
		count--
		return 0
	}

	system("cp -fL " source " " new_root "/" rel_path)
}

function make_tarball(flag) {
	tarball = g_instroot ".tar.gz"
	printf("Generating source tarball %s%s%s%s ...\n", RED, BOL, tarball, NC)

	if (pretend || SKIP_END)
		exit 0

	system("tar zcf " tarball " " g_instroot)
	if (flag ~ /purge/)
		system("rm -r "g_instroot)
}

# dirname
function dirname(path) {
	if (path == "")
		return ""

	# Remove the ending '/'
	gsub(/\/+$/, "", path)

	# Remove basename
	gsub(/[^\/]+$/, "", path)
	if (path == "") return "."

	# Remove the ending '/' again
	gsub(/\/+$/, "", path)
	if (path == "")
		return "/"

	return path
}

# basename
function basename(path) {
	if (path == "")
		return ""

	# Remove the ending '/'
	gsub(/\/+$/, "", path)
	if (path == "")
		return "/"

	path = gensub(/^.+\/+(.+)$/, "\\1", "g", path)

	return path;
}

###### Test #########
function do_test() {
	printf("%s%s%s%s\n", BLU, BOL, "---- Test dirname ----", NC)
	test_dirname("/home/abc");
	test_dirname("home///abc//");
	test_dirname("home///abc/de//");
	test_dirname("../abc//");
	test_dirname("abc");
	test_dirname("..");
	test_dirname("..///");

	printf("%s%s%s%s\n", BLU, BOL, "---- Test basename ----", NC)
	test_basename("/home//abc")
	test_basename("///")
	test_basename("/")
	test_basename("..")
	test_basename("../abc//")
	test_basename("/../abc//")
	test_basename("/../abc/efg/")
}

function test_dirname(path) {
	printf("dirname(%s) is \n  %s%s%s\n", path, GRN, dirname(path), NC)
}

function test_basename(path) {
	printf("basename(%s) is \n %s%s%s\n", path, GRN, basename(path), NC)
}
