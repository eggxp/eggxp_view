import os

for root, dirs, files in os.walk("./"):
    if root.find(".git") != -1:
        continue
    for file in files:
        result = os.path.join(root, file)
        print "" + result[2:]

os.system("pause")
