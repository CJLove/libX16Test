#!/usr/bin/env python3
#
# Wrapper script which runs an X16 program in the emulator (optionally under `xrdb-run`)
#
import sys
import argparse
import struct
import os.path
from subprocess import run

# Map for mapping escaped upper-case characters from the emulator back to upper-case
char_map = {
    '\\\\xc1':'A',
    '\\\\xc2':'B',
    '\\\\xc3':'C',
    '\\\\xc4':'D',
    '\\\\xc5':'E',
    '\\\\xc6':'F',
    '\\\\xc7':'G',
    '\\\\xc8':'H',
    '\\\\xc9':'I',
    '\\\\xca':'J',
    '\\\\xcb':'K',
    '\\\\xcc':'L',
    '\\\\xcd':'M',
    '\\\\xce':'N',
    '\\\\xcf':'O',
    '\\\\xd0':'P',
    '\\\\xd1':'Q',
    '\\\\xd2':'R',
    '\\\\xd3':'S',
    '\\\\xd4':'T',
    '\\\\xd5':'U',
    '\\\\xd6':'V',
    '\\\\xd7':'W',
    '\\\\xd8':'X',
    '\\\\xd9':'Y',
    '\\\\xda':'Z',
    '\\\\xa4':'_',
    '\\n':'\n'
}

def parse_result_from_file():
    with open('dump.bin','rb') as dump:
        ram = dump.read(4*1024)

    return ram[0x00] == 0

def cleanup_dump():
    for item in os.listdir(os.getcwd()):
        if item.endswith(".bin"):
            os.remove(os.path.join(os.getcwd(), item))


def main():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter,
        description='Run a unit test program in the X16 emulator')
    parser.add_argument('--prg', help='test program name',type=str)
    parser.add_argument('--emulator', help='full path to X16 emulator',type=str, default='x16emu')
    parser.add_argument('--xvfb', action='store_true', help='run emulator under xrdb-run', default=False)
    args = parser.parse_args()

    # Build commandline for running emulator and specified test program
    emulatorCmd=[]
    if args.xvfb:
        emulatorCmd.append('xvfb-run')

    # Run emulator with -dump R
    emulatorCmd.extend([args.emulator, '-dump', 'R', '-prg', args.prg, '-echo', '-run'])

    # Remove old dump files
    cleanup_dump()

    ret = run(emulatorCmd, capture_output=True)

    if ret.returncode != 0:
        print("Error running emulator, tests not run")
        print(ret.stderr)
        sys.exit(1)

    # Parse the result (PASS or FAIL) from the dump.bin file
    result = parse_result_from_file()

    # Reformat stdout captured from running the emulator
    # - strip output prior to unit tests starting

    stdout = str(ret.stdout)
    start = stdout.find('RUNNING')
    stdout = stdout[start:].lower()
    finish = stdout.find('dumped system')
    stdout = stdout[:finish]
    for key in char_map:
        stdout = stdout.replace(key,char_map[key])

    # Output the reformatted stdout
    print(stdout)

    # Remove old dump files
    cleanup_dump()

    # Result TRUE indicates all tests passed, so exit code should reflect PASS or FAIL
    if result:
        sys.exit(0)
    else:
        sys.exit(1)



if __name__ == '__main__':
    main()





