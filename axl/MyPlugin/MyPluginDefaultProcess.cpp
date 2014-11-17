// /////////////////////////////////////////////////////////////////
// Generated by axel-plugin wizard
// /////////////////////////////////////////////////////////////////

/* (C) MyCompany */


/* Put a short description of your plugin here */

/* MyCompany-contact@mycompany.com-http://www.mycompany.com */

#include "MyPluginDefaultProcess.h"

#include "MyPluginPlugin.h"

#include <QtGui/qvector3d.h>
#include <QtCore/qmath.h>

//#include <mypkg/my_class.h>
#include <axlCore/axlAbstractData.h>
#include <axlCore/axlSphere.h>
#include <axlCore/axlMesh.h>
#include <axlCore/axlpoint.h>

#include <dtkCore/dtkAbstractProcessFactory.h>
#include <dtkCore/dtkAbstractDataFactory.h>

// /////////////////////////////////////////////////////////////////
// MyPluginDefaultProcessPrivate
// /////////////////////////////////////////////////////////////////

class MyPluginDefaultProcessPrivate
{
public:
    QPair<axlMesh *, axlPoint *> input;
    double parameter;
    axlMesh *output;
};

// /////////////////////////////////////////////////////////////////
// MyPluginDefaultProcess
// /////////////////////////////////////////////////////////////////

MyPluginDefaultProcess::MyPluginDefaultProcess(void) : dtkAbstractProcess(), d(new MyPluginDefaultProcessPrivate)
{
	d->input.first = NULL;
	d->parameter = 0;
    d->output = NULL;
}

MyPluginDefaultProcess::~MyPluginDefaultProcess(void)
{
    delete d;
    
    d = NULL;
}

QVector3D MyPluginDefaultProcess::normal_temp(double thr_p0,double thr_p1,double thr_p2,double thr_p3,double thr_p4,double thr_p5,double thr_p6,double thr_p7,double thr_p8)
{
    QVector3D v1 =  QVector3D(thr_p0,thr_p1,thr_p2);
    QVector3D v2 =  QVector3D(thr_p3,thr_p4,thr_p5);
    QVector3D v3 =  QVector3D(thr_p6,thr_p7,thr_p8);
	return QVector3D::normal(v1,v2,v3);
}
void MyPluginDefaultProcess::setInput(dtkAbstractData *data, int channel)
{
    if(channel==0)
        d->input.first = dynamic_cast<axlMesh *>(data);
    else if(channel==1)
        d->input.second = dynamic_cast<axlPoint *>(data);
    else
        qDebug()<<"Only two channel available : 0 or 1";
}
void MyPluginDefaultProcess::setParameter(double a)
{
	d->parameter = a;
}

dtkAbstractData *MyPluginDefaultProcess::output(void)
{
    return d->output;
}

//Intersection : to find the intersection of a plane and a line
//Parameter: 
//           A: normal vector of the plane
//           u: a point of the plane
//           U: direction vector of the line
//           v: a point of the line
//Outout: The point is the intersection of the plane and the line. 
//         Type : QVector3D
QVector3D MyPluginDefaultProcess::Intersection(QVector3D A,QVector3D u,QVector3D U, QVector3D v)
{
   qreal t1 = 0;
   qreal t2 = 0;
   t1 = A.x()*(u.x()-v.x())+A.y()*(u.y()-v.y())+A.z()*(u.z()-v.z());
   t2 = A.x()*U.x()+A.y()*U.y()+A.z()*U.z();
   qreal t = t1/t2;
   return QVector3D(U.x()*t+v.x(),U.y()*t+v.y(),U.z()*t+v.z());
}
//Point_distance: Return a point which have the given distance from the point of a plane (direction: normal vector)
//Parameter: 
//           N: normal vector of the plane
//     p_plane: the point
//     dt     : distance
QVector3D MyPluginDefaultProcess::Point_distance(QVector3D N,QVector3D p_plane,qreal dt)
{
  return QVector3D(p_plane.x()+dt*N.x(),p_plane.y()+dt*N.y(),p_plane.z()+dt*N.z());
}
int MyPluginDefaultProcess::update(void)
{

	axlMesh *output1 = new axlMesh();
	double d1 = d->parameter;
	bool IsPlanar = false;//the last 4 points are planar or not? 
	QVector3D v1,v2,v3,v4,r1,tmp_n_i,tmp_n_j,tmp,tmp1,tmp2,dir_v;
	/*int count = 0;*/
    for (int i =0;i<d->input.first->vertex_count()-2;i++)
    { 
		if(i==d->input.first->vertex_count()-3)//for last loop
		{
			v1 = QVector3D(d->input.first->vertexX(i+2),d->input.first->vertexY(i+2),d->input.first->vertexZ(i+2));
			r1 = Point_distance(tmp_n_j,v1,d1);
			output1->push_back_vertex(r1.x(),r1.y(),r1.z());
		}
		else
		{
		  if (i==0)//for first loop to set up some initial conditions
          {
			  v1 = QVector3D(d->input.first->vertexX(i)  ,d->input.first->vertexY(i)  ,d->input.first->vertexZ(i));
	          v2 = QVector3D(d->input.first->vertexX(i+1),d->input.first->vertexY(i+1),d->input.first->vertexZ(i+1));
	          v3 = QVector3D(d->input.first->vertexX(i+2),d->input.first->vertexY(i+2),d->input.first->vertexZ(i+2));
		      v4 = QVector3D(d->input.first->vertexX(i+3),d->input.first->vertexY(i+3),d->input.first->vertexZ(i+3));
	          tmp_n_i = QVector3D::normal(v1,v2,v3);
        
              r1 = Point_distance(tmp_n_i,v1,d1);
		      output1->push_back_vertex(r1.x(),r1.y(),r1.z());//the fisrt vertex of output
			  
			  if(QVector3D::dotProduct(tmp_n_i,operator-(v4,v1))==0)//check that these 4 points are planar or not
			  {
				  tmp1 = Point_distance(tmp_n_i,v2,d1);
				  output1->push_back_vertex(tmp1.x(),tmp1.y(),tmp1.z());
				  IsPlanar = true;
				  tmp_n_j=tmp_n_i;

			  }
			  else
			  {
              tmp_n_j = QVector3D::normal(v2,v3,v4);
		      if(QVector3D::dotProduct(tmp_n_i,tmp_n_j)<0)
			       tmp_n_j = tmp_n_j.operator*=(-1); //change the direction of normal vector to ensure the shape of output mesh 
   
			  dir_v = operator-(v2,v1);
              tmp = Point_distance(tmp_n_j,v2,d1);
		      tmp1 = Intersection(tmp_n_j,tmp,dir_v,r1);
			  output1->push_back_vertex(tmp1.x(),tmp1.y(),tmp1.z());

			  dir_v = operator-(v3,v1);
              tmp2 = Intersection(tmp_n_j,tmp1,dir_v,r1);
		      output1->push_back_vertex(tmp2.x(),tmp2.y(),tmp2.z());
			  }           
         }
		else
	     {
		   v1 = v2;
		   v2 = v3;
		   v3 = v4; 
		   v4 = QVector3D(d->input.first->vertexX(i+3),d->input.first->vertexY(i+3),d->input.first->vertexZ(i+3));
		   tmp_n_i = tmp_n_j;
		   r1 = tmp1;
			   if(QVector3D::dotProduct(tmp_n_i,operator-(v4,v1))==0)
			   {
				   tmp1 = Point_distance(tmp_n_i,v2,d1);
				   output1->push_back_vertex(tmp1.x(),tmp1.y(),tmp1.z());
				   IsPlanar = true;
				   tmp_n_j=tmp_n_i;
			   }
			   else
				{
				   tmp_n_j = QVector3D::normal(v2,v3,v4);
				   if(QVector3D::dotProduct(tmp_n_i,tmp_n_j)<0)
						   tmp_n_j = tmp_n_j.operator*=(-1);
				   if(IsPlanar ==true)
				   {
					   dir_v = operator-(v2,v1);
					   tmp = Point_distance(tmp_n_j,v2,d1);
					   tmp1 = Intersection(tmp_n_j,tmp,dir_v,r1);
					   output1->push_back_vertex(tmp1.x(),tmp1.y(),tmp1.z());  
				   }
				   else
				   {
					   tmp1 = tmp2;
				   }
				   IsPlanar = false;    
				   dir_v = operator-(v3,v1);
				   tmp2 = Intersection(tmp_n_j,tmp1,dir_v,r1);
				   output1->push_back_vertex(tmp2.x(),tmp2.y(),tmp2.z());
				}
		 }
	  }
	}
	QVector<axlMesh::Edge> tmp_edge = d->input.first->edgeSet();

	//keep the edge and mesh of input -> mesh offset
	for(int i = 0; i<tmp_edge.size();i++)
	{
		output1->push_back_edge(tmp_edge[i]);
	}
	QVector<axlMesh::Face> tmp_face = d->input.first->faceSet();
    for(int i = 0; i<tmp_face.size();i++)
	{
		output1->push_back_face(tmp_face[i]);
	}
	//set the color
	output1->setColor(QColor(255,0,0));
	d->output = output1;
    return 1;
}

QString MyPluginDefaultProcess::form() const {
    return QString(
                " INPUT 0 data Input \n"
                " OUTPUT Data ");
}

bool MyPluginDefaultProcess::registered(void)
{
    return MyPluginPlugin::processFactSingleton->registerProcessType("MyPluginDefaultProcess", createMyPluginDefaultProcess, "axlAbstractDefault");
}

QString MyPluginDefaultProcess::description(void) const
{
    return "My MyPluginDefaultProcess description";
}

QString MyPluginDefaultProcess::identifier(void) const
{
    return "MyPluginDefaultProcess";
}

// /////////////////////////////////////////////////////////////////
// Type instanciation
// /////////////////////////////////////////////////////////////////

dtkAbstractProcess *createMyPluginDefaultProcess(void)
{
    return new MyPluginDefaultProcess;
}

