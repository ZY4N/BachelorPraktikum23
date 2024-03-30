import subprocess
import os

rosbag_path = "/home/sera/Documents/RosBags/Recorder_2023-08-01-11-39-20_c_l.bag"


def validatePogramm(command) -> bool:
    print(f"Running Command: {command}")
    result = subprocess.run(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, shell=True).returncode == 0
    print("OK." if result else "ERROR!")
    return result


def clean(all):
    os.system(f"rm -rf /tmp/mapdata")
    if not all:
        try:
            os.mkdir("/tmp/map_data")
        except OSError:
            pass

    return True


clean(False)

if validatePogramm("./drm_input_node"):
    print("All Tests passed.")
else:
    print("Last Test failed. Aborting.")

clean(True)
