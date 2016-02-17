BEGIN {
	version = "0.1.3"
	printf("link-parser, v%s\n", version)

	true = 1
	false = 0
	g_pat_srccommon = "\\/sw\\/vobs.+"
	g_sroot = ""
	inst_root = ""
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

	# Skip head lines
	getline
}

/^[^-]/ {
	link = $0
	# Remove the ending ' \'
	gsub(/[ \t]+\\$/, "", link)

	if (g_sroot == "") {
		printf("Grabbing sources and headers ...\n")
		g_sroot = get_sroot(link)
		"date +%Y%m%d-%H%M%S" | getline date
		inst_root = g_sroot"-"date
	}

	cmd_file = link".cmd"
	while ((getline line < cmd_file) > 0) {
		# abosolute path
		if (line ~ /[ \t]+-c[ \t]+\/.+$/)
			source = gensub(/^.+[ \t]+-c[ \t]+(.+)$/, "\\1", "g", line)
		else # relative path
			source = gensub(/^cd (.+);.+-c (.+)/, "\\1/\\2", "g", line)

		gsub(/esam\/objects\/([^\/]+\/){2,}sources\/src/, "dsl/sw/flat", source)
		sources[source]++
		#rel_install(source, g_sroot, inst_root)

		split(line, a, " ")
		prefix = gensub(/^cd (.+);.+/, "\\1", "g", line)
		for (i in a) {
			if (a[i] ~ /^-I/) {
				gsub(/^-I/, "", a[i])
				gsub(/esam\/objects\/([^\/]+\/)\{2,}sources\/src/, "dsl/sw/flat", a[i])
				if (a[i] ~ /^\//)
					includes[a[i]]++
				else
					includes[prefix "/" a[i]]++
			}
		}
	}

	close(cmd_file)

	# ---------
	# Headers
	# ---------

#	gsub(/\.(obj|o|lib)$/, "", link)
#	dep_file = link ".D"
#
#	if ((getline < dep_file) < 0)
#		next
#
#	# Get path prefix
#	cur_path = $1
#	gsub(/^#/, "", cur_path)
#
#	while ((getline < dep_file) > 0) {
#		gsub(/:/, " ")
#		for (i = 1; i <= NF; i++) {
#			if ($i !~ /\.(h|hpp)$/)
#				continue
#			header = cur_path "/" $i
#			rel_install(header, g_sroot, inst_root)
#		}
#	}
#	close(dep_file)
}

END {
	if (SKIP_END)
		exit 0
	print "Total dumped files: " count
	
	for (i in sources)
		rel_install(i, g_sroot, inst_root)

	for (i in includes) {

		#rel_install(i, g_sroot, inst_root)
	}

	if (arg ~ /tar/)
		make_tarball(arg)
}

function get_include(line) {
	inc = gensub(/^(-[^I]+|[^-]+) -I(.+)/, "\\2", "g")
}

function rel_install(source, rel_root, new_root) {
	count++
	
	dir = dirname(source)
	base = basename(source)
	patt = "^.+\\/"rel_root"\\/(sw.+)"
	rel_path = gensub(patt, "\\1", "g", dir)

	if (destdir)
		new_root = destdir "/" new_root

	if (pretend) {
		print source > rel_root".source.list"
		print rel_path"/"base > rel_root".relative.list"
		return 0
	}

	system("mkdir -p " new_root "/" rel_path)
	system("cp -Lr " source " " new_root "/" rel_path)
}

function make_tarball(flag) {
	tarball = inst_root ".tar.gz"
	printf("Generating source tarball %s%s%s%s ...\n", RED, BOL, tarball, NC)

	if (pretend || SKIP_END)
		exit 0

	"pwd" |getline oldpwd
	if (destdir)
		system("cd " destdir)

	system("tar zcf " tarball " " inst_root)
	if (flag ~ /purge/)
		system("rm -r "inst_root)

	if (destdir)
		system("cd " oldpwd)
}

function get_sroot(line) {
	if (line !~ g_pat_srccommon)
		return ""

	gsub(g_pat_srccommon, "", line);
	gsub(/.+\//, "", line);
	return line;
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
	printf("%s%s%s%s\n", BLU, BOL, "---- Test get_sroot ----", NC)
	test_get_sroot("/repo/lulinw/isam/sw/vobs/esam/build");
	test_get_sroot("/repo/lulinw/isam/sw/esam/build");

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

function test_get_sroot(line) {
	if ((ret = get_sroot(line)) == "") {
		printf("Unexpected line [PAT=%s]:\n  %s%s%s\n",
				g_pat_srccommon, RED, line, NC)
	} else
		printf("Root of %s is\n  %s%s%s\n", line, GRN, get_sroot(line), NC)
}

function test_dirname(path) {
	printf("dirname(%s) is \n  %s%s%s\n", path, GRN, dirname(path), NC)
}

function test_basename(path) {
	printf("basename(%s) is \n %s%s%s\n", path, GRN, basename(path), NC)
}
