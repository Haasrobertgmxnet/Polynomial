from tkinter import *
import numpy as np
import matplotlib.pyplot as plt
import calcrootsmodule as cr

class Poly:
    coeffs= []
    roots= []
    def __init__(self, entries):
        self.entries= entries
    def get_entries(self):
        for elem in self.entries:
            z=complex(float(elem[0].get()),float(elem[1].get()))
            self.coeffs.append(z)
        from tkinter import messagebox
        messagebox.showinfo("Title",'Hello, Coeff: {:.3f}'.format(self.coeffs[0].real))
    def calc_roots(self):
        self.get_entries()
        self.roots= cr.calc_roots(self.coeffs[0], self.coeffs[1], self.coeffs[2], self.coeffs[3], self.coeffs[4])
    def plot_roots(self):
        self.calc_roots()
        import matplotlib.pyplot as plt
        fig, ax = plt.subplots()
        X = [x.real for x in self.coeffs]
        Y = [x.imag for x in self.coeffs]
        ax.scatter(X,Y, color='blue', label='Coefficients', alpha=0.5, edgecolors='none')
        X = [x.real for x in self.roots]
        Y = [x.imag for x in self.roots]
        ax.scatter(X,Y, color='green', label='Roots', alpha=0.5, edgecolors='none')
        ax.legend()
        ax.grid(True)
        plt.title('Coefficients and Solutions')
        plt.xlabel('Real axis')
        plt.ylabel('Imaginary axis')
        plt.show()

root = Tk()
root.title('Hallo')
root.geometry("600x300")

Label(root, text="real part: ").grid(row=0, column=0)
a1 = DoubleVar()
textbox1 = Entry(root, textvariable=a1)
textbox1.grid(row=0, column=1)

entry_fields= []
coeffs= []

for i in range(0,5):
    Label(root, text="real part: ").grid(row=i, column=0)
    a1 = DoubleVar()
    textbox1 = Entry(root, textvariable=a1)
    textbox1.grid(row=i, column=1)

    Label(root, text="imag part: ").grid(row=i, column=2)
    a2 = DoubleVar()
    textbox1 = Entry(root, textvariable=a2)
    textbox1.grid(row=i, column=3)
    entry_fields.append((a1,a2))
    
poly= Poly(entry_fields)

calc_button = Button(root, text="Calcular", command= poly.calc_roots)
calc_button.grid(row=7, column=1)

my_button = Button(root, text="Muestra dibujo", command=poly.plot_roots)
my_button.grid(row=7, column=2)

ex_button = Button(root, text="Salir ahora", command=root.quit)
ex_button.grid(row=7, column=3)

root.mainloop()