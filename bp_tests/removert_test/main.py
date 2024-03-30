import time
import subprocess
import io
'''
pr = subprocess.Popen(["roslaunch", "removert", "run_kitti.launch"],stdout=subprocess.PIPE, stderr=subprocess.PIPE)

for line in io.TextIOWrapper(pr.stderr):
    print(line)

    if line.find("[For verification]") != -1:
        print("Found '[For verification] message. Done.")
        print("Killing Process...")
        pr.kill()
        print("OK.")


    pr.wait()


print(())
'''

with open("hi.txt", "bw") as file:
    file.write(b'afefaencfeioas\xe4eafef')

try:
    with open("hi.txt") as f:
        l = f.readlines()
        print(l)
except Exception as e:
    print((e))