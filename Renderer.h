#ifndef __OBJECTS_RENDERER_H
#define __OBJECTS_RENDERER_H

#include <GL/gl.h>

namespace Objects
{

	class Renderer
	{

		template<class InputIterator>
		void renderWireframes(InputIterator first, InputIterator last)
		{
			for (; first != last; first++) {
				glPushMatrix();
				translate(first->x);
				displayWireframeBox(first->bb);
				glPopMatrix();
			}
		}

		template<class Box>
		inline void renderWireframe(const Box &b)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(b.ll[0], b.ll[1], b.ll[3]);
			glVertex3f(b.ur[0], b.ll[1], b.ll[3]);
			glVertex3f(b.ur[0], b.ur[1], b.ll[3]);
			glVertex3f(b.ll[0], b.ur[1], b.ll[3]);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glVertex3f(b.ll[0], b.ll[1], b.ur[3]);
			glVertex3f(b.ur[0], b.ll[1], b.ur[3]);
			glVertex3f(b.ur[0], b.ur[1], b.ur[3]);
			glVertex3f(b.ll[0], b.ur[1], b.ur[3]);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(b.ll[0], b.ll[1], b.ll[3]);
			glVertex3f(b.ll[0], b.ll[1], b.ur[3]);
			glVertex3f(b.ur[0], b.ll[1], b.ll[3]);
			glVertex3f(b.ur[0], b.ll[1], b.ur[3]);
			glVertex3f(b.ur[0], b.ur[1], b.ll[3]);
			glVertex3f(b.ur[0], b.ur[1], b.ur[3]);
			glVertex3f(b.ll[0], b.ur[1], b.ll[3]);
			glVertex3f(b.ll[0], b.ur[1], b.ur[3]);
			glEnd();
		}

		inline void vertex(const std::vector<float>& v)
		{
			glVertex3f(v[0], v[1], v[2]);
		}

		inline void color(const std::vector<float>& v)
		{
			glColor3f(v[0], v[1], v[2]);
		}

		inline void translate(const std::vector<float>& v)
		{
			glTranslatef(v[0], v[1], v[2]);
		}
		
	};

}

#endif
