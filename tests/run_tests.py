from pathlib import Path

from Tester import Tester

ACTUAL_CMD = "ls"
MY_CMD = str(Path("../ft_ls").resolve())
TEST_FILES_DIR = str(Path("./generated_files").resolve())

tester = Tester(actual_cmd=ACTUAL_CMD, my_cmd=MY_CMD, test_files_dir=TEST_FILES_DIR)

print("Testing basic options on current directory")
tester.create_temp_dir()
tester.test()
tester.test("-l")
tester.test("-R")
tester.test("-a")
tester.test("-r")
tester.test("-t")
