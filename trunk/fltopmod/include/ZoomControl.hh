/* $Id: ZoomControl.hh,v 1.1 2006/09/04 19:22:53 stuart Exp $ */

#ifndef _ZOOM_CONTROL_HH_

#define _ZOOM_CONTROL_HH_

// Class for a zoom controller
// Implements zooming by scaling in the current XY plane

#include "Vector3d.hh"
#include "Matrix4x4.hh"
#include "Inlines.hh"

class ZoomControl
{
  protected :

     Matrix4x4 mNow;                                   // Current transformation matrix
     bool dragging;
     double vNowx, vDownx;                             // Mouse x coordinate
     Vector3d zNow, zDown;                             // Current zoom, etc.

  public :

     ZoomControl()                           // Default constructor
       : mNow(), dragging(false), vNowx(0.0), vDownx(0.0), zNow(1,1,1), zDown(1,1,1)
       {}

     ZoomControl(const ZoomControl& tc) // Copy constructor
       : mNow(tc.mNow), dragging(tc.dragging), vNowx(tc.vNowx), vDownx(tc.vDownx),
         zNow(tc.zNow), zDown(tc.zDown)
       {}

     ~ZoomControl()                          // Destructor
       {}

     ZoomControl& operator = (const ZoomControl& tc)
       {
         mNow = tc.mNow; dragging = tc.dragging; vNowx = tc.vNowx; vDownx = tc.vDownx;
         zNow = tc.zNow; zDown = tc.zDown;
         return (*this);
       }

     void reset(void)
       {
         zNow.set(1,1,1); zDown.set(1,1,1); mNow.reset();
       }
     
     void mouse(const Vector3d& pos)                   // Specify mouse position
       {
         vNowx = pos[0];
       }

     void mouse(double x, double y, double z=0.0)      // Specify mouse position
       {
         vNowx = x;
       }

     void mouse(double x)                              // Specify mouse x coordinate
       {
         vNowx = x;
       }
     
     Matrix4_4 value(void) const                       // Get the translation matrix
       {
         return mNow;
       }

     Vector3d zoom_value(void) const                  // Get the scale vector
       {
         return zNow;
       }
     
     void beginDrag(void)                              // Begin a drag
       {
         dragging = true; vDownx = vNowx;
       }
     
     void endDrag(void)                                // End a drag
       {
         dragging = false; zDown = zNow;
       }

     bool isDragging(void) const                       // Check dragging status
       {
         return dragging;
       }

     void update(void)                                 // Update the vectors and matrices
       {
         if ( dragging )
            {
              zNow = zDown;

                 // Mapping between mouse movement and scale change is as follows
                 // For a mouse movement of 1.0, scale changes by a factor of 2
                 // Note: This is in the transformed mouse coordinates (-1 to 1)
                 // Also only the x mouse coordinate is used
              double diff = vNowx - vDownx;
              double fact = 1 + Abs(diff);
              if ( diff < 0.0 ) zNow /= fact;
              else zNow *= fact;

                 // All 3 coordinates of the zoom vector are changed to get proper
                 // view scaling (rotate after zoom, etc.)

                 /*
                   NOTE : Since matrix is diagonal, no transposing required
                 */
              mNow[0][0] = zNow[0];
              mNow[1][1] = zNow[1];
              mNow[2][2] = zNow[2];
            }
       }
};

#endif /* #ifndef _ZOOM_CONTROL_HH_ */


/*
  $Log: ZoomControl.hh,v $
  Revision 1.1  2006/09/04 19:22:53  stuart
  Added includes and libs.

  Revision 2.2  2000/05/02 19:08:48  vinod
  *** empty log message ***

  Revision 2.1  2000/03/20 19:55:05  vinod
  Zoom controller using scaling

*/
