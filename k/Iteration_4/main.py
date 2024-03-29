import subprocess
import os

rosbag_path = "/home/sera/Documents/RosBags/Recorder_2023-08-01-11-39-20_c_l.bag"
pprm = "/home/sera/Desktop/pycharm-community-2023.3.5/bin/slam6d-code/bin/peopleremover"
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

if validatePogramm(f"./drm_input_node {rosbag_path} -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 2min --frame-format uos")\
        and validatePogramm(f"{pprm} -j10 --voxel-size=10 --maxrange-method=normals -e 30 --normal-method=angle -f uos /tmp/map_data")\
        and clean(False)\
        and validatePogramm(f"./drm_input_node {rosbag_path} -o /tmp/map_data --max-radial-dist 30 --max-peripheral-dist 20 --time-per-block 2min --frame-format kitti")\
        and validatePogramm("roslaunch removert run_kitti.launch")\
        and clean(True):
    print("All Tests passed.")
else:
    print("Last Test failed. Aborting.")

