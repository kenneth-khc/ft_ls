import difflib
import errno
import fcntl
import os
import pty
import select
import struct
import subprocess
import termios
from pathlib import Path


class Tester:
    test_num: int = 1
    actual_cmd: str
    my_cmd: str
    test_files_dir: str
    visualize_whitespaces: bool

    RED: str = "\033[31m"
    GREEN: str = "\033[32m"
    RESET: str = "\033[0m"

    def __init__(
        self,
        actual_cmd: str,
        my_cmd: str,
        test_files_dir: str,
        visualize_whitespaces: bool = True,
    ) -> None:
        self.actual_cmd = actual_cmd
        self.my_cmd = my_cmd
        self.test_files_dir = test_files_dir
        self.visualize_whitespaces = visualize_whitespaces

    def test(self, args: str | list[str] | None = None):
        if isinstance(args, str):
            args = [args]
        expected_output = Tester.run_in_pty(
            cwd=self.test_files_dir, cmd=self.actual_cmd, args=args
        )
        expected = (
            Tester.show_ws(expected_output)
            if self.visualize_whitespaces
            else expected_output
        )
        actual_output = Tester.run_in_pty(
            cwd=self.test_files_dir, cmd=self.my_cmd, args=args
        )
        actual = (
            Tester.show_ws(actual_output)
            if self.visualize_whitespaces
            else actual_output
        )
        delta = difflib.unified_diff(
            expected.splitlines(keepends=True),
            actual.splitlines(keepends=True),
            fromfile="ls",
            tofile="ft_ls",
        )
        if args:
            if isinstance(args, str):
                readable_cmd = f"{self.my_cmd} {args}"
            else:
                readable_cmd = f"{self.my_cmd} {''.join(args)}"
        else:
            readable_cmd = f"{self.my_cmd}"

        if diff_lines := "".join(delta):
            print(
                f"{Tester.RED}Test {Tester.test_num} KO{Tester.RESET} ({readable_cmd})"
            )
            print(diff_lines)
        else:
            print(
                f"{Tester.GREEN}Test {Tester.test_num} OK{Tester.RESET} ({readable_cmd})"
            )

        Tester.test_num += 1

    @staticmethod
    def show_ws(s: str) -> str:
        return s.replace(" ", "·").replace("\t", "→").replace("\n", "⏎\n")

    @staticmethod
    def run_in_pty(
        cmd: str,
        cwd: str = ".",
        args: list[str] | None = None,
        cols: int = 80,
        rows: int = 24,
        timeout: int = 5,
    ):
        master_fd, slave_fd = pty.openpty()
        _ = fcntl.ioctl(
            slave_fd, termios.TIOCSWINSZ, struct.pack("HHHH", rows, cols, 0, 0)
        )

        cmd_args = [cmd] + (args if args else [])
        proc = subprocess.run(
            cmd_args,
            cwd=cwd,
            stdin=subprocess.DEVNULL,
            stdout=slave_fd,
            stderr=slave_fd,
            close_fds=True,
            check=False,
        )
        os.close(slave_fd)
        chunks: list[bytes] = []
        try:
            while True:
                r, _, _ = select.select([master_fd], [], [], timeout)
                if not r:
                    raise TimeoutError("Timed out")
                try:
                    chunk = os.read(master_fd, 65536)
                except OSError as e:
                    if e.errno == errno.EIO:
                        break
                    raise
                if not chunk:
                    break
                chunks.append(chunk)
        finally:
            os.close(master_fd)
            # _ = proc.wait()

        return b"".join(chunks).decode("utf-8", "replace").replace("\r\n", "\n")

    @staticmethod
    def create_temp_dir():
        tmp_dir_name = "generated_files"
        Path(tmp_dir_name).mkdir(exist_ok=True)
        file_modes = (
            # Toggling each permission individually
            0o000,
            0o400,
            0o200,
            0o100,
            0o040,
            0o020,
            0o010,
            0o004,
            0o002,
            0o001,
            # All permissions on
            0o700,
            0o070,
            0o007,
            0o777,
            # Practical file modes
            0o644,
            0o600,
            0o755,
            0o700,
            0o400,
            0o444,
            0o664,
            0o775,
        )
        for i, file_mode in enumerate(file_modes):
            file_path = f"{tmp_dir_name}/file{i}"
            Path(file_path).touch(mode=file_mode)
            os.chmod(file_path, file_mode)
