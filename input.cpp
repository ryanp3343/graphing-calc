#include "input.h"

void input::step(int command)
{
    //from processing events

    //right increase range and regraph cordinates
    if(command==GORIGHT)
    {
        setXmax(_xmax+1);
        setXmin(_xmin+1);
        getCoordin();
    }
    //left decreases range and regraph cordinates
    else if(command==GOLEFT)
    {
        setXmin(_xmin-1);
        setXmax(_xmax-1);
        getCoordin();
    }


    else if(command==GOUP)
    {
        //increase the xyCord by the position of y vertex
        for(double xpix=0; xpix<= GRAPH_PANEl; xpix++)
        {
            xyCord[xpix].position.y += 100;
        }
        //clears and sets new position for x axis
        xAxis.clear();
        getXAx(xAxis[0].position.x, xAxis[0].position.y+100);
    }
    else if(command==GODOWN)
    {
        //decrease the xyCord by the postion of y vertex
        for(double xpix=0; xpix<= GRAPH_PANEl; xpix++)
        {
            xyCord[xpix].position.y -= 100;
        }
        //clears and sets new position for x axis
        xAxis.clear();
        getXAx(xAxis[0].position.x, xAxis[0].position.y-100);
    }

    //zoom in decrease range increase scale regraph cordinates
    else if(command==IN)
    {
        setXmin(_xmin*0.95);
        setXmax(_xmax*0.95);
        SCALE*=1.05;
        getCoordin();
    }
    //zoom out increase range deacrease scale regraph cordinates
    else if(command==OUT)
    {
        setXmin(_xmin*1.05);
        setXmax(_xmax*1.05);
        getCoordin();
        SCALE*=0.95;
    }
    //resets graph to orginal postion regraph cordinates
    else if(command==RESET)
    {
        setXmax(10);
        setXmin(-10);
        SCALE=1;
        getCoordin();
    }
    //bool for equation bar on screen
    else if(command==NEW)
    {
       please=true;

    }
    //bool for equation bar on screen
    else if(command==DELETE)
    {
       please=false;

    }
    //changes the type of the xy line
    else if(command==IDK)
    {
        xyCord.setPrimitiveType(LinesStrip);
    }

    //changes the type of the xy line
    else if(command==IDK2)
    {
        xyCord.setPrimitiveType(Points);
    }

}


void input::getCoordin()
{
    //clear the vertex array
    xyCord.clear();

    double range=_xmax-_xmin;
  //  cout<<"RANGE: "<<range<<endl;
    double prevX;
    double prevY;
    double prevYPix;

    for(double xpix=0; xpix<=GRAPH_PANEl; xpix++)
    {
        //xval from screen

        double xval=_xmin +(xpix/GRAPH_PANEl)*range;    //graph 2044

        //yval from evalution from rpn function
        double yval=g.Evaluate(postfix,xval)*SCALE;
      //cout<<"XVAL: "<<xval<<" YVAL: "<<yval<<endl;

        //amount of pixels based on how many xpixels on screen
        _ypixel=(1-(yval/_grids))*SCREEN_HEIGHT/2;   //height 675
      //cout<<"YPIXEL: "<<_ypixel<<endl;

        //plot x axis in middle of xvals
        if(prevX<=0 && xval>=0)
        {
            getYAx(xpix,_ypixel);
        }
        //plot y axis in middle of yvals
        if(prevY<=0 && yval>=0)
        {
            getXAx(xpix,(_ypixel));
        }

        //vertex of graph line
        Vertex vertex;
        //position in relation to x and y cord
        vertex.position=Vector2f(xpix,_ypixel);
        vertex.color=Color(58,185,54);
        //append the vertex to x and y cordinates
        xyCord.append(vertex);


       prevX=xval;
       prevY=yval;
       prevYPix=_ypixel;
    }
}

void input::Draw(RenderWindow &window)
{
    //draws brackround, x/y axis, and graph line
    if(please==false)
    {
        window.clear();
        window.draw(_back);
        window.draw(yAxis);
        window.draw(xAxis);
        window.draw(xyCord);
    }
    //draws backround, x/y axis, graph line and box to input expression
    if(please==true)
    {
        window.clear();
        window.draw(_back);
        window.draw(yAxis);
        window.draw(xAxis);
        window.draw(xyCord);
        window.draw(userBox);
    }

}

//make x axis
void input::getXAx(double x, double y)
{
    //append vertex array from left most to middle, middle and middle to right most
    xAxis.clear();
    Vertex xVertex[2];
    xVertex[0].position = Vector2f(0, y);
    xVertex[0].color = Color(255,255,255);
    xAxis.append(xVertex[0]);
    xVertex[1].position = Vector2f(GRAPH_PANEl, y);
    xVertex[1].color = Color(255,255,255);
    xAxis.append(xVertex[1]);


}
//make y axis
void input::getYAx(double x, double y)
{
    //appends vertex array from top most to middle to bottom most
    yAxis.clear();
    Vertex yVertex[2];
    yVertex[0].position = Vector2f(x, 0);
    yVertex[0].color = Color(255,255,255);
    yAxis.append(yVertex[0]);
    yVertex[1].position = Vector2f(x, SCREEN_HEIGHT);
    yVertex[1].color = Color(255,255,255);
    yAxis.append(yVertex[1]);

}
