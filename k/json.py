import os
import argparse
import json
import subprocess


def validatePogramm(command) -> bool:
    return subprocess.run(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True).returncode == 0


def rec(item) -> str:
    s = ""

    if isinstance(item, dict):
        for k in item.keys():
            s += f"{k}: "
            s += rec(item[k])

    elif isinstance(item, list):
        for x in item:
            s += rec(x)

    else:
        s += f"{str(item)} "

    return s


parser = argparse.ArgumentParser(
    prog="Meta JSON Reader",
    description="Verifies that the Metadata from the dynamic railmap project ist readable and prints it.",
    epilog="Example Command ./main.py <path_to_dir>"
)

parser.add_argument('path_to_dir', default="./")
args = parser.parse_args()

dir_without_meta = False
error_while_reading_json = False

for directory in os.listdir(args.path_to_dir):
    path = f"{args.path_to_dir}/{directory}/meta.json"
    if not os.path.isfile(path):
        dir_without_meta = True
        continue
    local_error = False
    try:
        with open(path, "r", encoding="latin-1") as file:
            print(path)
            lines = file.readlines()
    except IOError:
        error_while_reading_json = True
        local_error = True

    try:
        print(rec(json.loads("".join(lines))))

    except json.JSONDecodeError:
        error_while_reading_json = True
        local_error = True

    if local_error:
        print("ERROR!")
    else:
        print("OK.")

print()
print()
if error_while_reading_json:
    print("FAIL: At least one ERROR occurred while reading and decoding the json files")
else:
    print("SUCCESS: No ERRORS occurred while reading and decoding the json files")

if dir_without_meta:
    print("WARNING: There was a directory without meta.json File")

