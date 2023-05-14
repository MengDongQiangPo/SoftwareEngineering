import tkinter as tk
from tkinter import messagebox
import os

current_dir = os.getcwd()
script_dir = os.path.dirname(os.path.abspath(__file__))

def generate_exercises():
    max_num = int(max_num_entry.get())
    operators = operators_entry.get()
    num_operators = int(num_operators_entry.get())
    has_bracket = bracket_var.get()
    has_decimal = decimal_var.get()
    num_exercises = int(num_exercises_entry.get())
    output_type = output_var.get()
    file_path = file_path_entry.get()
    command = script_dir + f'\math_kernel.exe {max_num} {operators} {num_operators} {has_bracket} {has_decimal} {num_exercises} {output_type} {file_path}'
    os.system(command)

    if output_type == 2:
        messagebox.showinfo("提示", "题目已输出到文件: "+ file_path)

root = tk.Tk()
root.title("操作题生成器")

# 最大数
max_num_label = tk.Label(root, text="请输入最大数：")
max_num_label.pack()
max_num_entry = tk.Entry(root)
max_num_entry.pack()
max_num_entry.insert(tk.END, "10")  # 设置默认值为10
# 运算符
operators_label = tk.Label(root, text="请输入运算符（+ - * /):")
operators_label.pack()
operators_entry = tk.Entry(root)
operators_entry.pack()
operators_entry.insert(tk.END, "+")  # 设置默认值为'+'

# 运算符个数
num_operators_label = tk.Label(root, text="请输入运算符个数：")
num_operators_label.pack()
num_operators_entry = tk.Entry(root)
num_operators_entry.pack()
num_operators_entry.insert(tk.END, "2")  # 设置默认值为2

# 是否有括号
bracket_label = tk.Label(root, text="是否有括号(y/n):")
bracket_label.pack()
bracket_var = tk.StringVar(value="n")
bracket_radio_yes = tk.Radiobutton(root, text="是", variable=bracket_var, value="y")
bracket_radio_yes.pack()
bracket_radio_no = tk.Radiobutton(root, text="否", variable=bracket_var, value="n")
bracket_radio_no.pack()

# 是否有小数
decimal_label = tk.Label(root, text="是否有小数(y/n):")
decimal_label.pack()
decimal_var = tk.StringVar(value="n")
decimal_radio_yes = tk.Radiobutton(root, text="是", variable=decimal_var, value="y")
decimal_radio_yes.pack()
decimal_radio_no = tk.Radiobutton(root, text="否", variable=decimal_var, value="n")
decimal_radio_no.pack()

# 题目数量
num_exercises_label = tk.Label(root, text="请输入题目数量：")
num_exercises_label.pack()
num_exercises_entry = tk.Entry(root)
num_exercises_entry.pack()
num_exercises_entry.insert(tk.END, "10")  # 设置默认值为10

# 输出方式
output_label = tk.Label(root, text="请选择输出方式(1. 输出到控制台 2. 输出到文件）：")
output_label.pack()
output_var = tk.IntVar(value=1)
output_radio_console = tk.Radiobutton(root, text="输出到控制台", variable=output_var, value=1)
output_radio_console.pack()
output_radio_file = tk.Radiobutton(root, text="输出到文件", variable=output_var, value=2)
output_radio_file.pack()

# 文件路径
file_path_label = tk.Label(root, text="请输入文件路径：")
file_path_label.pack()
file_path_entry = tk.Entry(root)
file_path_entry.pack()
file_path_entry.insert(tk.END, script_dir + "\exercises.txt")  # 设置默认值为'exercises.txt'

# 生成按钮
generate_button = tk.Button(root, text="生成", command=generate_exercises)
generate_button.pack()

root.mainloop()
