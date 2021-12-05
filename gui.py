import tkinter as tk
import tkinter.filedialog as tkfd
from tkinter import ttk
from enum import Enum
from shim import *


# Definitions

class Mode(Enum):
    ENCODE = "ENCODE"
    DECODE = "DECODE"

algorithms = ["alg1", "alg2", "alg3"]


# Functions

def choose_img_enc():
    global in_img_path_var_enc
    path = tkfd.askopenfilename(filetypes=[("PNG", "*.png"), ("Bitmap", "*.bmp")])
    in_img_path_var_enc.set(path)

def choose_file():
    global in_secret_path_var
    path = tkfd.askopenfilename(filetypes=[("All Files", "*.*")])
    in_secret_path_var.set(path)

def choose_img_dec():
    global in_img_path_var_dec
    path = tkfd.askopenfilename(filetypes=[("PNG", "*.png"), ("Bitmap", "*.bmp")])
    in_img_path_var_dec.set(path)

def hide_data():
    global in_img_path_var_enc, in_secret_path_var, alg_dropdown, out_file_entry
    encode(in_img_path_var_enc.get(), in_secret_path_var.get(), alg_dropdown.get(), out_file_entry.get())

def find_data():
    global in_img_path_var_dec, alg_multiselect, out_file_loc_entry
    algorithms = [alg_multiselect.get(i) for i in alg_multiselect.curselection()]
    decode(in_img_path_var_dec.get(), algorithms, out_file_loc_entry.get())

def change_mode():
    global mode
    if mode == Mode.ENCODE:
        set_mode_decode()
    else:
        set_mode_encode()

def set_mode_encode():
    global mode, mode_text_var, encode_widgets, decode_widgets
    mode = Mode.ENCODE
    mode_text_var.set(f'Current Mode: {mode.value}')
    for widget in decode_widgets:
        widget.pack_forget()
    for widget in encode_widgets:
        widget.pack()

def set_mode_decode():
    global mode, mode_text_var, encode_widgets, decode_widgets
    mode = Mode.DECODE
    mode_text_var.set(f'Current Mode: {mode.value}')
    for widget in encode_widgets:
        widget.pack_forget()
    for widget in decode_widgets:
        widget.pack()

def pack_with_static_label(master, label_text, widget):
    label = tk.Label(master, text=label_text)
    label.pack(side=tk.LEFT)
    widget.pack(side=tk.RIGHT)

def pack_with_variable_label(master, widget, label_text):
    widget.pack(side=tk.LEFT)
    label_text_var = tk.StringVar()
    label_text_var.set(label_text)
    label = tk.Label(master, textvariable=label_text_var)
    label.pack(side=tk.RIGHT)
    return label_text_var


# Window

window = tk.Tk()
window.title("HACStego")


# Main Widgets

mode_row = tk.Frame(window)
mode_button = tk.Button(mode_row, text="CHANGE MODE", command=change_mode)
mode_text_var = pack_with_variable_label(mode_row, mode_button, "")

spacer = tk.Label(window, text="")

mode_row.pack()
spacer.pack()


# Encode Mode Widgets

in_img_row_enc = tk.Frame(window)
in_img_button_enc = tk.Button(in_img_row_enc, text="Choose Image To Encode", command=choose_img_enc)
in_img_path_var_enc = pack_with_variable_label(in_img_row_enc, in_img_button_enc, "(No File Selected)")

in_secret_row = tk.Frame(window)
in_secret_button = tk.Button(in_secret_row, text="Choose File To Hide", command=choose_file)
in_secret_path_var = pack_with_variable_label(in_secret_row, in_secret_button, "(No File Selected)")

alg_row = tk.Frame(window)
alg_dropdown = ttk.Combobox(alg_row, values=algorithms)
pack_with_static_label(alg_row, "Select Encoding Algorithm:", alg_dropdown)

out_file_row = tk.Frame(window)
out_file_entry = tk.Entry(out_file_row)
pack_with_static_label(out_file_row, "Output File Path:", out_file_entry)

hide_data_button = tk.Button(window, text="Hide Data", command=hide_data)

encode_widgets = [in_img_row_enc, in_secret_row, alg_row, out_file_row, hide_data_button]


# Decode Mode Widgets

in_img_row_dec = tk.Frame(window)
in_img_button_dec = tk.Button(in_img_row_dec, text="Choose Image To Decode", command=choose_img_dec)
in_img_path_var_dec = pack_with_variable_label(in_img_row_dec, in_img_button_dec, "(No File Selected)")

alg_label = tk.Label(window, text="Select Decoding Algorithms To Try:")
alg_multiselect = tk.Listbox(window, selectmode="multiple")
alg_multiselect.insert(0, *algorithms)

out_file_loc_row = tk.Frame(window)
out_file_loc_entry = tk.Entry(out_file_loc_row)
pack_with_static_label(out_file_loc_row, "Output File Location Path:", out_file_loc_entry)

hide_data_button = tk.Button(window, text="Find Data", command=find_data)

decode_widgets = [in_img_row_dec, alg_label, alg_multiselect, out_file_loc_row, hide_data_button]


# Start

set_mode_encode()

window.mainloop()
