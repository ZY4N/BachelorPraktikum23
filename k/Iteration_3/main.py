import io
import subprocess
import os

rosbag_path = "/home/sera/Documents/RosBags/Recorder_2023-08-01-11-39-20_c_l.bag"
pprm = "/home/sera/Desktop/pycharm-community-2023.3.5/bin/slam6d-code/bin/peopleremover"
def validatePogramm(command) -> bool:
    print(f"Running Command: {command}")
    pr = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)

    result = pr.wait() == 0
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

if validatePogramm(f"./drm_input_node {rosbag_path} -o /tmp/map_data")\
        and validatePogramm(f"{pprm} -j10 --voxel-size=10 --maxrange-method=normals --normal-method=angle -f uos /tmp/map_data -e 30"):
    print("All Tests passed.")
else:
    print("Last Test failed. Aborting.")



#validatePogramm(f"{pprm} -j10 --voxel-size=10 --maxrange-method=normals --normal-method=angle -f uos /tmp/map_data -e 10")
clean(True)
