import subprocess
import os

def encode(in_img_path, in_secret_path, algorithm, arg, out_file_path):
    print(f'Hiding file {in_secret_path} in image {in_img_path} using {algorithm} with argument {arg} and writing out to {out_file_path}')

def decode(in_img_path, algorithm, arg, out_file_loc_path):
    print(f'Attempting to find data in image {in_img_path} using {algorithm} with argument {arg} and writing out files to the directory {out_file_loc_path}')
    if (arg == None):
        arg = "0"
    print("./build/hacstego.x "+algorithm+" "+arg+" "+out_file_loc_path)
    os.system("./build/hacstego.x "+algorithm+" "+arg+" "+out_file_loc_path)