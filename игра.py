# подключаем графическую библиотеку
from tkinter import *
# подключаем модули, которые отвечают за время и случайные числа
import time
import random
# создаём новый объект — окно с игровым полем. В нашем случае переменная окна называется tk, и мы его сделали из класса Tk() — он есть в графической библиотеке 
tk = Tk()
# делаем заголовок окна — Games с помощью свойства объекта title
tk.title('Game')
# запрещаем менять размеры окна, для этого используем свойство resizable 
tk.resizable(0, 0)
# помещаем наше игровое окно выше остальных окон на компьютере, чтобы другие окна не могли его заслонить. Попробуйте :)
tk.wm_attributes('-topmost', 1)
# создаём новый холст — 400 на 500 пикселей, где и будем рисовать игру
canvas = Canvas(tk, width=500, height=400, highlightthickness=0)
# говорим холсту, что у каждого видимого элемента будут свои отдельные координаты 
canvas.pack()
# обновляем окно с холстом
tk.update()
# Описываем класс Ball, который будет отвечать за шарик 
class Ball:
    # конструктор — он вызывается в момент создания нового объекта на основе этого класса
    def __init__(self, canvas, paddle, score, color):
        # задаём параметры объекта, которые нам передают в скобках в момент создания
        self.canvas = canvas
        self.paddle = paddle
        self.score = score

        self.id = canvas.create_oval(10,10, 25, 25, fill='green')
        # помещаем шарик в точку с координатами 245,100
        self.canvas.move(self.id, 245, 100)
        # задаём список возможных направлений для старта
        starts = [-2, -1, 1, 2]
        # перемешиваем его 
        random.shuffle(starts)
        # выбираем первый из перемешанного — это будет вектор движения шарика
        self.x = starts[0]
        # в самом начале он всегда падает вниз, поэтому уменьшаем значение по оси y
        self.y = -2
        # шарик узнаёт свою высоту и ширину
        self.canvas_height = self.canvas.winfo_height()
        self.canvas_width = self.canvas.winfo_width()
        # свойство, которое отвечает за то, достиг шарик дна или нет. Пока не достиг, значение будет False
        self.hit_bottom = False
    # обрабатываем касание платформы, для этого получаем 4 координаты шарика в переменной pos (левая верхняя и правая нижняя точки)
    def hit_paddle(self, pos):
        # получаем кординаты платформы через объект paddle (платформа)
        paddle_pos = self.canvas.coords(self.paddle.id)
        # если координаты касания совпадают с координатами платформы
        if pos[2] >= paddle_pos[0] and pos[0] <= paddle_pos[2]:
            if pos[3] >= paddle_pos[1] and pos[3] <= paddle_pos[3]:
                # увеличиваем счёт (обработчик этого события будет описан ниже)
                self.score.hit()
                # возвращаем метку о том, что мы успешно коснулись
                return True
        # возвращаем False — касания не было
        return False
    # метод, который отвечает за движение шарика
    def draw(self):
        self.canvas.move(self.id, self.x, self.y)
        pos = self.canvas.coords(self.id)
        if pos[1] <= 0:
            self.y = 2
        if pos[3] >= self.canvas_height:
            self.hit_bottom = True
            canvas.create_text(250, 120, text='Вы проиграли', font=('Courier', 30), fill='red')
        if self.hit_paddle(pos) == True:
            self.y = -2
        if pos[0] <= 0:
            self.x = 2
        if pos[2] >= self.canvas_width:
            self.x = -2
class Paddle:
    def __init__(self, canvas, color):
        self.canvas = canvas
        self.id = canvas.create_rectangle(0, 0, 100, 10, fill='orange')
        start_1 = [40, 60, 90, 120, 150, 180, 200]
        random.shuffle(start_1)
        self.starting_point_x = start_1[0]
        self.canvas.move(self.id, self.starting_point_x, 300)
        self.x = 0
        self.canvas_width = self.canvas.winfo_width()
        self.canvas.bind_all('<KeyPress-Right>', self.turn_right)
        self.canvas.bind_all('<KeyPress-Left>', self.turn_left)
        self.started = False
        self.canvas.bind_all('<KeyPress-Return>', self.start_game)
    def turn_right(self, event):
        self.x = 2
    def turn_left(self, event):
        self.x = -2
    def start_game(self, event):
        self.started = True
    def draw(self):
        self.canvas.move(self.id, self.x, 0)
        pos = self.canvas.coords(self.id)
        if pos[0] <= 0:
            self.x = 0
        elif pos[2] >= self.canvas_width:
            self.x = 0
class Score:
    def __init__(self, canvas, color):
        self.score = 0
        self.canvas = canvas
        self.id = canvas.create_text(450, 10, text=self.score, font=('Courier', 15), fill=color)
    def hit(self):
        self.score += 1
        self.canvas.itemconfig(self.id, text=self.score)
score = Score(canvas, 'green')
paddle = Paddle(canvas, 'White')
ball = Ball(canvas, paddle, score, 'red')
while not ball.hit_bottom:

    
    if paddle.started == True:
        ball.draw()
        paddle.draw()
    tk.update_idletasks()
    tk.update()
    time.sleep(0.01)
time.sleep(3)
