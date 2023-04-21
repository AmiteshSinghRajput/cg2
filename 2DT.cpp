#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <graphics.h>
#include <iostream>
#define COORD_SHIFT 100

using namespace std;

void clrscr()
{
#ifdef _WIN32
  system("cls");
#elif __unix__
  system("clear");
#endif
}

double **inputFigure(int n)
{
  cout << "Enter the matrix for the 2-D shape (homogeneous):\n";

  double **figure = NULL;
  figure = new double *[n];

  for (int i = 0; i < n; i++)
  {
    figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
      cin >> figure[i][j];
    }
  }

  return figure;
}

void drawFigure(double **points, int n)
{
  for (int i = 0; i < n; i++)
  {
    line(COORD_SHIFT + points[i][0],
         COORD_SHIFT + points[i][1],
         COORD_SHIFT + points[(i + 1) % n][0],
         COORD_SHIFT + points[(i + 1) % n][1]);
  }

}

double **translate(double **figure, int dim, int m, int n)
{
  double **_figure = NULL;
  int T[dim][3] = {{1, 0, 0}, {0, 1, 0}, {m, n, 1}};

  _figure = new double *[dim];

  for (int i = 0; i < dim; i++)
  {
    _figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
        _figure[i][j] = 0;
      for (int k = 0; k < dim; k++)
      {
        _figure[i][j] += figure[i][k] * T[k][j];
      }
    }
  }
  return _figure;
}

double **rotate(double **figure, int dim, double theta)
{
  double **_figure = NULL;
  double T[dim][3] = {{cos(theta * M_PI / 180.0), sin(theta * M_PI / 180.0), 0},
                      {-sin(theta * M_PI / 180.0), cos(theta * M_PI / 180.0), 0},
                      {0, 0, 1}};

  _figure = new double *[dim];

  for (int i = 0; i < dim; i++)
  {
    _figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
        _figure[i][j] = 0;
      for (int k = 0; k < dim; k++)
      {
        _figure[i][j] += figure[i][k] * T[k][j];
      }
    }
  }

  return _figure;
}

double **scale(double **figure, int dim, int m, int n)
{
  double **_figure = NULL;
  int T[dim][3] = {{m, 0, 0}, {0, n, 0}, {0, 0, 1}};

  _figure = new double *[dim];

  for (int i = 0; i < dim; i++)
  {
    _figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
        _figure[i][j] = 0;
      for (int k = 0; k < dim; k++)
      {
        _figure[i][j] += figure[i][k] * T[k][j];
      }
    }
  }

  return _figure;
}

double **reflect(double **figure, int dim, int c)
{
  double **_figure = NULL;
  int T[dim][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  switch (c)
  {
  case 1:
    T[1][1] = -1;
    break;
  case 2:
    T[0][0] = -1;
    break;
  case 3:
    T[0][0] = 0;
    T[0][1] = 1;
    T[1][0] = 1;
    T[1][1] = 0;
    break;
  case 4:
    T[0][0] = -1;
    T[1][1] = -1;
    break;
  default:
    return NULL;
    break;
  }

  _figure = new double *[dim];

  for (int i = 0; i < dim; i++)
  {
    _figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
        _figure[i][j] = 0;
      for (int k = 0; k < dim; k++)
      {
        _figure[i][j] += figure[i][k] * T[k][j];
      }
    }
  }

  return _figure;
}

double **shear(double **figure, int dim, int m, int n)
{
  double **_figure = NULL;
  int T[dim][3] = {{1, n, 0}, {m, 1, 0}, {0, 0, 1}};

  _figure = new double *[dim];

  for (int i = 0; i < dim; i++)
  {
    _figure[i] = new double[3];
    for (int j = 0; j < 3; j++)
    {
        _figure[i][j] = 0;
      for (int k = 0; k < dim; k++)
      {
        _figure[i][j] += figure[i][k] * T[k][j];
      }
    }
  }

  return _figure;
}

void menu(double **figure, int dim)
{
  int ch = 0;
  double **_figure;

  do
  {
    clrscr();
    cout << "\nMenu\n-------\n(1) Translation\n(2) Rotation";
    cout << "\n(3) Scaling\n(4) Reflection\n(5) Shearing";
    cout << "\n(6) View Figure\n(7) Exit\n\nEnter Choice: ";
    cin >> ch;
    cout << endl;
    cleardevice();
    switch (ch)
    {
        case 1:
            int tx,n, m,ty;

            cout << "Enter translation in x-axis: ";
            cin >> m;
            cout << "Enter translation in y-axis: ";
            cin >> ty;

            _figure = translate(figure, dim, tx, ty);
            
            setcolor(RED);
            
            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);
            delay(1000);
            setcolor(YELLOW);
            cout << "Drawing Transformed Figure...\n";
            drawFigure(_figure, dim);
            delay(2000);
            break;
        case 2:
            double theta;

            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);
            delay(1000);
            cout << "Enter rotation angle (degrees): ";
            cin >> theta;

            _figure = rotate(figure, dim, theta);

            cout << "Drawing Transformed Figure...\n";
            drawFigure(_figure, dim);
            delay(2000);
            break;
        case 3:
            int sx,sy;
            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);
            delay(1000);

            cout << "Enter scaling in x-axis: ";
            cin >> sx;
            cout << "Enter scaling in y-axis: ";
            cin >> sy;
            _figure = scale(figure, dim, sx, sy);

            cout << "Drawing Transformed Figure...\n";
            drawFigure(_figure, dim);
            delay(2000);
            break;
        case 4:

            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);
            cout << "Reflect along\n(1) x-axis\n(2) y-axis\n(3) y = x\n(4) y = -x\n"
                << "\nEnter Choice: ";
            cin >> m;
            delay(1000);
            _figure = reflect(figure, dim, m);

            cout << "Drawing Transformed Figure...\n";
            drawFigure(_figure, dim);
            delay(2000);
            break;
        case 5:
            int shx,shy;
            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);

            cout << "Enter shearing in x-axis: ";
            cin >> shx;
            cout << "Enter shearing in y-axis: ";
            cin >> shy;
            _figure = shear(figure, dim, shx, shy);
            cout << "Drawing Transformed Figure...\n";
            drawFigure(_figure, dim);
            delay(1000);
            break;
        case 6:
            cout << "Drawing Original Figure...\n";
            drawFigure(figure, dim);
            break;
        case 7:
            exit(0);
            break;
        default:
            break;
    }

    delete _figure;

    cout << endl
         << "Finished..."
         << endl;

    if (ch != 7)
    {
      cout << "\nPress Enter to continue ...\n";
      cin.ignore();
      cin.get();
    }
  } while (ch != 7);
};

int main(void)
{
  int n;
  double **fig;
  int gd = DETECT, gm;

  initgraph(&gd, &gm, NULL);

  cout << "Enter number of points in the figure: ";
  cin >> n;

  fig = inputFigure(n);

  menu(fig, n);

  delete fig;
  closegraph();

  return 0;
}
