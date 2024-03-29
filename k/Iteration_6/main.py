import subprocess
import os
import json

rosbag_path = "/home/sera/Documents/RosBags/Recorder_2023-08-01-11-39-20_c_l.bag"
pprm = "/home/sera/Desktop/pycharm-community-2023.3.5/bin/slam6d-code/bin/peopleremover"


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


def validatePogramm(command) -> bool:
    print(f"Running Command: {command}")
    result = subprocess.run(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True).returncode == 0
    print("OK." if result else "ERROR!")
    return result


def meta_json(path):
    error_while_reading_json = False
    path = ""
    for directory in os.listdir(path):
        path = f"{path}/{directory}/meta.json"
        if not os.path.isfile(path):
            continue
        try:
            with open(path, "r", encoding="latin-1") as file:
                print(path)
                lines = file.readlines()
        except IOError:
            error_while_reading_json = True
            break

        try:
            print(rec(json.loads("".join(lines))))

        except json.JSONDecodeError:
            error_while_reading_json = True
            break

    if error_while_reading_json:
        print(f"FAIL: An ERROR occurred while reading and decoding the json file {path}")
        return False
    else:
        print("SUCCESS: No ERRORS occurred while reading and decoding the json files ")
        return True


def clean(all):
    os.system(f"rm -rf /tmp/mapdata")
    if not all:
        try:
            os.mkdir("/tmp/map_data")
        except OSError:
            pass

    return True


if validatePogramm(f"./drm_input_node {rosbag_path} -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 2min --max-scan-pos-deviation 1 --chunk-size 30 --frame-format uos")\
        and validatePogramm(f"{pprm} -j10 --voxel-size=10 --maxrange-method=normals --normal-method=angle -f uos /tmp/map_data/chunk0_0/frames")\
        and meta_json("/tmp/map_data")\
        and clean()\
        and validatePogramm(f"./drm_input_node {rosbag_path} --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 2min --max-scan-pos-deviation 1 --chunk-size 30 --frame-format kitti")\
        and validatePogramm("roslaunch removert run_kitti.launch")\
        and meta_json("/tmp/map_data")\
        and clean():
    print("All Tests passed.")
else:
    print("Last Test failed. Aborting.")