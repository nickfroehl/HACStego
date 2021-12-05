def encode(in_img_path, in_secret_path, algorithm, out_file_path):
    print(f'Hiding file {in_secret_path} in image {in_img_path} using {algorithm} and writing out to {out_file_path}')

def decode(in_img_path, algorithms, out_file_loc_path):
    print(f'Attempting to find data in image {in_img_path} using {algorithms} and writing out files to the directory {out_file_loc_path}')
