#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <GL/glut.h>   // The GL Utility Toolkit (Glut) Header
#include <iostream>
#include <utility>

#define WIDTH 500
#define HEIGHT 500

/*
vector in 3d space
*/

template <typename T>
struct vec3
{
	T x;
	T y;
	T z;
	vec3() : x(0.0), y(0.0), z(0.0) {}
	vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	vec3(T i) : x(i), y(i), z(i) {}

	vec3 operator * (const vec3& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		this->z *= rhs.z;
		return *this;
	}

	vec3 operator + (const vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}
};

/*
Representation of a point
*/
struct Point
{
	int x;
	int y;
	vec3<float> c; //color
	Point() : x(1), y(1) {}
	Point(int _x, int _y) : x(_x), y(_y) {}
	Point(int _x, int _y, vec3<float> _c) : x(_x), y(_y), c(_c.x, _c.y, _c.z) {}
	Point& operator=(const Point& rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	bool operator!=(const Point& rhs)
	{
		if (this->x != rhs.x || this->y != rhs.y)
			return true;
		return false;
	}
	bool operator<(const Point& rhs) const
	{
		if (this->x < rhs.x) return true;
		else if (this->x > rhs.x) return false;
		else return (this->y < rhs.y);
	}
	bool operator>(const Point& rhs) const
	{
		if (this->x > rhs.x) return true;
		else if (this->x < rhs.x) return false;
		else return (this->y > rhs.y);
	}
	Point operator * (const Point& rhs)
	{
		this->x *= rhs.x;
		this->y *= rhs.y;
		return *this;
	}
	void replacePoints(const int& _x, const int& _y)
	{
		this->x = _x;
		this->y = _y;
	}
};


void init_window()
                 /* Clear the image area, and set up the coordinate system */
{

        					       /* Clear the window */
        glClearColor(0.0,0.0,0.0,0.0);
		glShadeModel(GL_SMOOTH);
        glOrtho(0,WIDTH,0,HEIGHT,-1.0,1.0);
}

/***************************************************************************/

void write_pixel(int x, int y, vec3<float> c)
                                         /* Turn on the pixel found at x,y */
{

        //glColor3f (intensity, intensity, intensity);    
		glColor3f(c.x, c.y, c.z);             
        glBegin(GL_POINTS);
           glVertex3i( x, y, 0);
        glEnd();	
}


class Circle final
{
	/*Directional Components*/
	vec3<float> center;
	float radius;

	/*Color Components*/
	vec3<float> surfaceColor; //color of object
	vec3<float> emissionColor; //what color light it emits
	float transparency;
	float reflection;

    
public:
	constexpr Circle() = delete;
	~Circle() = default;

	/*use R value constructor*/
	explicit Circle(
					 const vec3<float>&& _center,
					 const float&&       _radius,
					 const vec3<float>&& _surfaceColor, //color of object
					 const vec3<float>&& _emissionColor, //what color light it emits
					 const float&&       _transparency = 0.0,
					 const float&&       _reflection = 0.0
				   ) noexcept
				   : center       (std::exchange(center, _center)),
				     radius       (std::exchange(radius, _radius)),
					 surfaceColor (std::exchange(surfaceColor, _surfaceColor)),
					 emissionColor(std::exchange(emissionColor, _emissionColor)),
					 transparency (std::exchange(transparency, _transparency)),
					 reflection   (std::exchange(reflection, _reflection))
	{}

	inline constexpr float radiusSquared() noexcept { return radius*radius; }
};

class RayTracer final
{
	struct Objects
	{
		std::vector<Circle> circles;

		//add objects here
		explicit Objects() noexcept 
		: circles() 
		{
		circles.emplace_back(std::move(Circle(vec3<float>(0.0, 100, 20), 200, vec3<float>(.20,.20,.20), vec3<float>(.20, .20, .20), .25, 1)));
		}
	};

	/*
	The Trace Function
	*/
	static vec3<float> trace(const vec3<float>&& raypos, const vec3<float>&& raydir)
	{
		return vec3<float>(.25,.25,.25);
	}

public:

	//objects in scene
	static Objects objects();

	/*
	The Render Function
	*/
    inline static void render()
    {
		vec3<float> pixelColor;
		for(int y = 0; y < HEIGHT; ++y)
			for(int x = 0; x < WIDTH; ++x)
			{
				//do some stuff

				pixelColor = trace(vec3<float>(0), vec3<float>(x,y,-1));
				write_pixel(x, y, pixelColor);
			}
    }
};

void display ( void )   // Create The Display Function
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	      // Clear Screen 
  

  // CALL YOUR CODE HERE
  RayTracer::render();

  glutSwapBuffers();                                      // Draw Frame Buffer 
}

int main(int argc, char *argv[])
{

	glutInit            ( &argc, argv ); 
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowSize  ( 500,500 ); 
	glutCreateWindow    ( "Computer Graphics" ); 
	glutDisplayFunc     ( display );  
	glutIdleFunc	    ( display );
	
        					      
        init_window();				             //create_window
						       		
	glutMainLoop        ( ); 
    //rayTracer.render();

    return 0;
}