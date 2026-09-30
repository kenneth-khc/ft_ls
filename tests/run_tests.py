from pathlib import Path

from Tester import Tester
import argparse

ACTUAL_CMD = "ls"
MY_CMD = str(Path("../ft_ls").resolve())
TEST_FILES_DIR = str(Path("./generated_files").resolve())

parser = argparse.ArgumentParser(prog="run_tests")
_ = parser.add_argument("-c", "--cols")
args = parser.parse_args()

tester = Tester(
    actual_cmd=ACTUAL_CMD,
    my_cmd=MY_CMD,
    test_files_dir=TEST_FILES_DIR,
    cols=int(args.cols) if args.cols else 86,
)

print("Testing files in current directory")
tester.create_temp_dir()
tester.test(args=["file0"])
tester.test(args=["file0", "file1"])
tester.test(args=["file0", "file1", "file2"])
tester.test(args=["file0", "file1", "file2", "file3"])
tester.test(args=["file0", "file1", "file2", "file3", "file4"])

print("Testing files in nested directories")
tester.test(args=["dir1/dir2/file1"])
tester.test(args=["dir1/dir2/file1", "dir1/dir2/file2"])
tester.test(args=["dir1/dir2/file1", "dir1/dir2/file2", "dir1/dir2/file3"])

print("Testing directories")
tester.test()
tester.test(args=["dir1"])
tester.test(args=["dir1", "dir1/dir2"])
# tester.test(args=["file0", "file1", "file2", "file3", "file4"])
# tester.test("-l")
# tester.test("-R")
# tester.test("-a")
# tester.test("-r")
# tester.test("-t")
