
#include<GL/glut.h>
double x0 = 0.40, y0 = 0.40, x1 = 0.70, y1 = 0.70;//monitor
double a0 = 0.525, b0 = 0.3, a1 = 0.575, b1 = 0.4;//base
double c0 = 0.45, d0 = 0.2, c1 = 0.65, d1 = 0.3;//base
double e0 = -0.55, f0 = 0.0, e1 = 0.55, f1 = 0.19;//conection
double p1 = -0.5, p2 = 0.19, p3 = -0.52, p4 = 0.15;//frame
double m0 = 0.45, n0 = 0.80, m1 = 0.5, n1 = 0.85;//buffer
float pkt_i = 0.02;//topdown
float pkt_j = 0.02;//side
float pkt_k = 0.02;//downtop
int data_pkt = 0, ack_pkt = 0;//to check stage
float d_TD = 0.02, d_side = 0.5, d_BU = 0.19;//data frame boundary values
float a_TD = -0.01, a_side = -0.575, a_BU = 0.19;//ack frame boundary values
int data_count = 0, ack_count = 0;//number data and ack received
double p5, p6, p7, p8;


void delay()//(frame delay)
{
int i, j;
j = 1500;
while (j != 0)
{
j--;
i = 18000;
while (i != 0)
i--;
}
}


void delay2()//(frame delay)
{
int i, j;
j = 100;
while (j != 0)
{
j--;
i = 18000;
while (i != 0)
i--;
}
}

void delay1()//for a 3 second delay(time out)
{
int i, j;
j = 15000;
while (j != 0)
{
j--;
i = 40000;
while (i != 0)
i--;
}
}

void drawstring(float x, float y, float z, const char *string)
{
const char *c;
glRasterPos3f(x, y, z);

for (c = string; *c != '\0'; c++)
{
glColor3f(1.0, 0.0, 0.0);
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
glFlush();
}
}


void monitor_draw(double x0, double y0, double x1, double y1)//draw the monitor's display part
{
glColor3f(1.0, 0.75, 0.2);
glBegin(GL_LINE_LOOP);
glVertex2f(x0, y0);
glVertex2f(x1, y0);
glVertex2f(x1, y1);
glVertex2f(x0, y1);
glEnd();
glFlush();
}



void base_draw(double a0, double b0, double c0, double d0, double a1, double b1, double c1, double d1)//draw the monitor's base part
{
glColor3f(1.0, 0.75, 0.2);
glBegin(GL_LINE_LOOP);
glVertex2f(a0, b1);
glVertex2f(a0, b0);
glVertex2f(c0, d1);
glVertex2f(c0, d0);
glVertex2f(c1, d0);
glVertex2f(c1, d1);
glVertex2f(a1, b0);
glVertex2f(a1, b1);
glEnd();
glFlush();
}

void connection() //draws connection line between 2 computers
{
glColor3f(0.0, 0.2, 1.0);
glBegin(GL_LINES);
glVertex2f(e0, f1);
glVertex2f(e0, f0);
glEnd();
glFlush();
glBegin(GL_LINES);
glVertex2f(e0, f0);
glVertex2f(e1, f0);
glEnd();
glFlush();
glBegin(GL_LINES);
glVertex2f(e1, f0);
glVertex2f(e1, f1);
glEnd();
glFlush();
}

void buffer_draw(double m0, double n0, double m1, double n1, int flag)
{
int count = 0;
for (float i = 0; i <= 0.25; i += 0.075)
{
glColor3f(1.0, 0.0, 0.0);//red
if (count < flag) glColor3f(0.0, 1.0, 0.0);//green
glBegin(GL_QUADS);
glVertex2f(m0 + i, n0);
glVertex2f(m1 + i, n0);
glVertex2f(m1 + i, n1);
glVertex2f(m0 + i, n1);
glEnd();
glFlush();
count++;
}
}

void computer() //to draw whole connection setup
{
for (float i = 0.01; i <= 1; i += 0.01)
{
float angle = i * 360;
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0, 0.0, 0.0);
glPushMatrix();
glScalef(i, i, 1);
glRotatef(angle, 0, 0,1);
monitor_draw(x0, y0, x1, y1);
monitor_draw(-x0, y0, -x1, y1);
monitor_draw(x0 + 0.02, y0 + 0.02, x1 - 0.02, y1 - 0.02);
monitor_draw(-x0 - 0.02, y0 + 0.02, -x1 + 0.02, y1 - 0.02);
base_draw(a0, b0, c0, d0, a1, b1, c1, d1);
base_draw(-a0, b0, -c0, d0, -a1, b1, -c1, d1);
drawstring(-0.65, 0.6, 0.0, "SENDER");
drawstring(0.45, 0.6, 0.0, "RECEIVER");
connection();
buffer_draw(m0, n0, m1, n1, 0);
buffer_draw(-m0 - 0.15, n0, -m1 - 0.15, n1, 0);
glPopMatrix();
glFlush();
delay2();
}
}


void draw_pkt()//to draw frame
{
glBegin(GL_POLYGON);
glVertex2f(p1, p2);
glVertex2f(p3, p2);
glVertex2f(p3, p4);
glVertex2f(p1, p4);
glEnd();
}

void call_trace()//to remove traces
{
glColor3d(0, 0, 0);
draw_pkt();
}

void packet_send()//to send data frame
{
glColor3f(0.0, 1.0, 0.0);
draw_pkt();

delay();
draw_pkt();

delay();

glFlush();
}

void packet_ack()//to send ack frame
{
glColor3f(0.0, 1.0, 1.0);
draw_pkt();
delay();
draw_pkt();
delay();
glFlush();
}

void packet_top_bottom(float ck)//frame moving from top to down
{
p5 = p1;
p6 = p2;
p7 = p3;
p8 = p4;
if (data_pkt == 0)//data
{
glPushMatrix();
while (p8 > ck) {
call_trace();
glTranslatef(0, -pkt_i, 0);
p6 -= pkt_i;
p8 -= pkt_i;
packet_send();
}
glPopMatrix();
}
else//ack
{
glPushMatrix();
while (p6 > ck) {
call_trace();
glTranslatef(0, -pkt_i, 0);
p6 -= pkt_i;
p8 -= pkt_i;
packet_ack();
}
glPopMatrix();
}
p1 = p5;
p2 = p6;
p3 = p7;
p4 = p8;
}

void packet_sideways(float ck)//frame moving sideways
{
p5 = p1;
p6 = p2;
p7 = p3;
p8 = p4;
if (data_pkt == 0)
{
glPushMatrix();
while (p7 < ck) {
call_trace();
glTranslatef(pkt_j, 0, 0);
p5 += pkt_j; p7 += pkt_j;
packet_send();
}
glPopMatrix();
}
else
{
glPushMatrix();
while (p7 > ck) {
call_trace();
glTranslatef(-pkt_j, 0, 0);
p5 -= pkt_j; p7 -= pkt_j;
packet_ack();
}
glPopMatrix();
}
p1 = p5;
p2 = p6;
p3 = p7;
p4 = p8;
}

void packet_bottom_top(float ck)//frame moving from bottom to top
{
p5 = p1;
p6 = p2;
p7 = p3;
p8 = p4;
if (data_pkt == 0)
{
glPushMatrix();
while (p6 < ck) {
call_trace();
glTranslatef(0, pkt_k, 0);
p6 += pkt_k; p8 += pkt_k;
packet_send();
}
glPopMatrix();
}
else
{
glPushMatrix();
while (p6 < ck) {
call_trace();
glTranslatef(0, pkt_k, 0);
p6 += pkt_k; p8 += pkt_k;
packet_ack();
}
glPopMatrix();
}
p1 = p5;
p2 = p6;
p3 = p7;
p4 = p8;
}
void display2(void)//title
{
glClear(GL_COLOR_BUFFER_BIT);
glLineWidth(3.0);
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_LINE_LOOP);
glVertex2f(10, 10);
glVertex2f(10, 490);
glVertex2f(490, 490);
glVertex2f(490, 10);
glEnd();
glColor3f(1.0, 1.0, 1.0);
drawstring(-0.25, 0.5, 0.0, "Topic: Stop-and-wait Protocol");
glColor3f(1.0, 1.0, 1.0);
drawstring(-0.25, 0.4, 0.0, "Submitted by:");
glColor3f(1.0, 1.0, 0.0);
drawstring(-0.25, 0.3, 0.0, "ELVIN DSA[4MT20CS059]");
glColor3f(1.0, 1.0, 0.0);
drawstring(-0.25, 0.2, 0.0, "DHANUSH SHETTY[4MT20CS052]");
glColor3f(1.0, 1.0, 0.0);
drawstring(-0.25, 0.1, 0.0, "6 CSE 1");
glFlush();
}
void display1()//intial display
{
display2();
delay1();
computer();
}

void restore_data()//to restore pkt(co-ordinates) after ack frame is recieved
{
p1 = -0.5, p2 = 0.19, p3 = -0.52, p4 = 0.15;//data frame
}

void restore_ack()////to restore pkt(co-ordinates) after data frame is recieved
{
p1 = 0.6, p2 = .19, p3 = .62, p4 = .15;//ack frame
}

void erase_string()//to erase the strings
{
glColor3f(0.0, 0.0, 0.0);
drawstring(+0.5, -0.5, 0.0, "packet dropped");
glColor3f(0.0, 0.0, 0.0);
drawstring(-0.65, -0.5, 0.0, "Data frame sending");
glColor3f(0.0, 0.0, 0.0);
drawstring(+0.5, -0.5, 0.0, "Data frame recieved");
glColor3f(0.0, 0.0, 0.0);
drawstring(+0.5, -0.6, 0.0, "Ack frame sending");
glColor3f(0.0, 0.0, 0.0);
drawstring(-0.65, -0.6, 0.0, "Ack frame received");
}

void data()//to send data frame
{
if (data_pkt == 0 && ack_count < 4)
{
data_count++;
packet_send();
drawstring(-0.65, -0.5, 0.0, "Data frame sending");
packet_top_bottom(d_TD);
if (d_TD == -1.0)
{
erase_string();
drawstring(+0.5, -0.5, 0.0, "packet dropped");
data_count--;
call_trace();
restore_data();
}
else
{
packet_sideways(d_side);
packet_bottom_top(d_BU);
erase_string();
drawstring(+0.5, -0.5, 0.0, "Data frame recieved");
data_pkt = 1;
call_trace();
restore_ack();
buffer_draw(m0, n0, m1, n1, data_count);
delay1();
erase_string();
}
}
else {
glColor3f(0.0, 1.0, 0.0);
drawstring(0.0, -0.5, 0.0, "Transmission Complete");
}
}

void ack()//to send ack frame
{
if (data_pkt == 1 && ack_count < 4)
{
ack_count++;
packet_ack();
drawstring(+0.5, -0.6, 0.0, "Ack frame sending");
packet_top_bottom(a_TD);
packet_sideways(a_side);
packet_bottom_top(a_BU);
erase_string();
drawstring(-0.65, -0.6, 0.0, "Ack frame received");
ack_pkt = 1;
data_pkt = 0;
call_trace();
restore_data();
buffer_draw(-m0 - 0.15, n0, -m1 - 0.15, n1, ack_count);
delay1();
erase_string();
}
else
{
glColor3f(0.0, 1.0, 0.0);
drawstring(0.0, -0.5, 0.0, "Transmission Complete");
}
}



void mouse(int btn, int state, int x, int y)//to start transmission
{
if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
data();
ack();
}
}
void menu(int n)
{
switch (n)
{
case 1:data();
ack();
break;

case 2: d_TD = -1.0;
data();
d_TD = 0.02;
break;

case 3:exit(0);
}
}

int main(int argc, char **argv)//main
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(500, 0);
glutInitWindowSize(850, 700);
glutCreateWindow("Stop-and-Wait Protocol");
glutDisplayFunc(display1);
glutCreateMenu(menu);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutAddMenuEntry("PACKET SUCCESSFULL TRANSMISSION", 1);
glutAddMenuEntry("PACKET DROPPING", 2);
glutMainLoop();
}
