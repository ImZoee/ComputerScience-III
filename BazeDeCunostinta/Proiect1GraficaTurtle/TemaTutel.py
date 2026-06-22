import turtle


screen = turtle.Screen()
screen.setup(width=800, height=450)
screen.title("Peisaj toamna")
screen.bgcolor("#9ec6ff")
screen.tracer(False)

pen = turtle.Turtle()
pen.hideturtle()
pen.speed(0)
pen.penup()


def draw_rectangle(t, x, y, width, height, color):
	t.goto(x, y)
	t.setheading(0)
	t.color(color)
	t.begin_fill()
	t.pendown()
	for _ in range(2):
		t.forward(width)
		t.left(90)
		t.forward(height)
		t.left(90)
	t.end_fill()
	t.penup()


def draw_line(t, x1, y1, x2, y2, color):
	t.goto(x1, y1)
	t.color(color)
	t.pendown()
	t.goto(x2, y2)
	t.penup()


def draw_tree(t, trunk_rect, foliage_dots):
	draw_rectangle(t, *trunk_rect)
	for x, y, size, color in foliage_dots:
		t.goto(x, y)
		t.dot(size, color)


def draw_bus_stop(t, rectangles, lines):
	for rect in rectangles:
		draw_rectangle(t, *rect)
	for line in lines:
		draw_line(t, *line)


def draw_bus_sign(t, rectangles, text_info):
	for rect in rectangles:
		draw_rectangle(t, *rect)
	x, y, color, font, message = text_info
	t.goto(x, y)
	t.color(color)
	t.write(message, align="center", font=font)
	t.penup()


def scatter_leaves(t, leaves):
	for x, y, size, color in leaves:
		t.goto(x, y)
		t.dot(size, color)


TREES = [
	(
		(-360, -220, 22, 170, "#7c5029"),
		[
			(-377, -20, 80, "#d86f29"),
			(-339, -5, 80, "#f2a65a"),
			(-354, 20, 80, "#b8501f"),
			(-319, -25, 80, "#f6c36d"),
			(-384, 5, 80, "#ec9248"),
		],
	),
	(
		(-250, -220, 22, 170, "#7c5029"),
		[
			(-267, -20, 80, "#d86f29"),
			(-229, -5, 80, "#f2a65a"),
			(-244, 20, 80, "#b8501f"),
			(-209, -25, 80, "#f6c36d"),
			(-274, 5, 80, "#ec9248"),
		],
	),
	(
		(280, -220, 22, 170, "#7c5029"),
		[
			(263, -20, 80, "#d86f29"),
			(301, -5, 80, "#f2a65a"),
			(286, 20, 80, "#b8501f"),
			(321, -25, 80, "#f6c36d"),
			(256, 5, 80, "#ec9248"),
		],
	),
	(
		(360, -220, 22, 170, "#7c5029"),
		[
			(343, -20, 80, "#d86f29"),
			(381, -5, 80, "#f2a65a"),
			(366, 20, 80, "#b8501f"),
			(401, -25, 80, "#f6c36d"),
			(336, 5, 80, "#ec9248"),
		],
	),
]

BUS_STOP_RECTANGLES = [
	(-120, -200, 12, 120, "#4a3c30"),
	(108, -200, 12, 120, "#4a3c30"),
	(-134, -80, 268, 26, "#36271f"),
	(-90, -175, 180, 80, "#d8e8f5"),
	(-76.8, -185, 153.6, 18, "#7b563a"),
	(-72, -167, 144, 10, "#9b6d48"),
]

BUS_STOP_LINES = [
	(-90, -175, -90, -95, "#aac7e4"),
	(90, -175, 90, -95, "#aac7e4"),
]

BUS_SIGN_RECTANGLES = [
	(140, -200, 6, 90, "#5f646e"),
	(119, -110, 48, 26, "#fef5d6"),
]

BUS_SIGN_TEXT = (143, -105, "#2d4d86", ("Arial", 12, "bold"), "BUS")

GROUND_LEAVES = [
	(-360, -216, 10, "#d86f29"),
	(-300, -218, 8, "#ec9248"),
	(-240, -212, 9, "#c75b1a"),
	(-180, -220, 7, "#f6c36d"),
	(-120, -214, 8, "#d86f29"),
	(-60, -219, 9, "#ec9248"),
	(0, -215, 7, "#c75b1a"),
	(60, -218, 10, "#f6c36d"),
	(120, -212, 8, "#d86f29"),
	(180, -220, 9, "#ec9248"),
	(240, -214, 7, "#c75b1a"),
	(300, -218, 8, "#f6c36d"),
	(360, -216, 10, "#d86f29"),
	(-330, -198, 7, "#ec9248"),
	(-270, -205, 8, "#f6c36d"),
	(-210, -196, 6, "#d86f29"),
	(-150, -202, 7, "#c75b1a"),
	(-90, -195, 8, "#ec9248"),
	(-30, -204, 7, "#f6c36d"),
	(30, -197, 8, "#d86f29"),
	(90, -203, 7, "#ec9248"),
	(150, -196, 6, "#c75b1a"),
	(210, -205, 7, "#f6c36d"),
	(270, -198, 8, "#d86f29"),
	(330, -204, 7, "#ec9248"),
]

FRONT_LEAVES = [
	(-140, -110, 8, "#f6c36d"),
	(-110, -98, 7, "#d86f29"),
	(-80, -86, 9, "#ec9248"),
	(-50, -95, 7, "#c75b1a"),
	(-20, -82, 8, "#f6c36d"),
	(10, -90, 7, "#d86f29"),
	(40, -80, 8, "#ec9248"),
	(70, -88, 6, "#c75b1a"),
	(100, -78, 7, "#f6c36d"),
	(130, -86, 8, "#d86f29"),
	(160, -76, 7, "#ec9248"),
	(190, -84, 6, "#c75b1a"),
	(220, -74, 8, "#f6c36d"),
	(-120, -60, 6, "#d86f29"),
	(-60, -52, 7, "#ec9248"),
	(0, -58, 8, "#f6c36d"),
	(60, -50, 7, "#c75b1a"),
	(120, -56, 6, "#d86f29"),
	(180, -48, 7, "#ec9248"),
]


draw_rectangle(pen, -420, -220, 840, 120, "#b77a46")
draw_rectangle(pen, -420, -220, 840, 38, "#d9c59a")
draw_rectangle(pen, -260, -220, 360, 34, "#c2b08c")

for trunk_rect, foliage in TREES:
	draw_tree(pen, trunk_rect, foliage)

draw_bus_stop(pen, BUS_STOP_RECTANGLES, BUS_STOP_LINES)
draw_bus_sign(pen, BUS_SIGN_RECTANGLES, BUS_SIGN_TEXT)

scatter_leaves(pen, GROUND_LEAVES)
scatter_leaves(pen, FRONT_LEAVES)

screen.update()
screen.mainloop()