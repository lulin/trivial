#!@include "functions.awk"

BEGIN {
	true = 1
	false = 0
	g_pat_srccommon = "\\/sw\\/vobs.+"
	g_sroot = ""
	tar_root = ""

	# Colors
	RED="\033[0;31m"
	GRN="\033[0;32m"
	BLU="\033[0;34m"
	NC="\033[0m"
	BOL="\033[1m"

	if (arg ~ /test/) {
		do_test();
		SKIP_END = true
		exit 0
	}
	count = 0
}

/^[^-]/ {
	link = $0
	# Remove the ending ' \'
	gsub(/[ \t]+\\$/, "", link)

	if (g_sroot == "") {
		g_sroot = get_sroot(link)
		system("mkdir ." g_sroot)
	}

	cmd_file = link".cmd"
	while ((getline line < cmd_file) > 0) {
		# abosolute path
		if (line ~ /[ \t]+-c[ \t]+\/.+$/)
			source = gensub(/^.+[ \t]+-c[ \t]+(.+)$/, "\\1", "g", line)
		# relative path
		else
			source = gensub(/^cd (.+);.+-c (.+)/, "\\1/\\2", "g", line)

		print BLU source NC
		if (source == "") {
			print RED "+++++++"line NC
		}

		dir = dirname(source)
		base = basename(source)
		patt = "^.+\\/"g_sroot"\\/(sw.+)"
		rel_path = gensub(patt, "\\1", "g", dir)

		system("mkdir -p ." g_sroot "/" rel_path)
		system("cp " source " ." g_sroot "/" rel_path)

		count = count + 1
	}
}

END {
	print "Total dumped files: " count
	"date +%Y%m%d%H%M%S" | getline date
	tarball = g_sroot "." date ".tar.gz"
	printf("Generating source tarball %s%s%s%s ...\n", RED, BOL, tarball, NC)
	system("tar zcf " tarball " ." g_sroot)
	system("rm -r ."g_sroot)
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
