#include "renderer.h"


//these hold the geometry of the sweepers and the mines
const int	 NumSweeperVerts = 16;
const SPoint sweeper[NumSweeperVerts] = {SPoint(-1, -1),
                                         SPoint(-1, 1),
                                         SPoint(-0.5, 1),
                                         SPoint(-0.5, -1),

                                         SPoint(0.5, -1),
                                         SPoint(1, -1),
                                         SPoint(1, 1),
                                         SPoint(0.5, 1),
                                         
                                         SPoint(-0.5, -0.5),
                                         SPoint(0.5, -0.5),

                                         SPoint(-0.5, 0.5),
                                         SPoint(-0.25, 0.5),
                                         SPoint(-0.25, 1.75),
                                         SPoint(0.25, 1.75),
                                         SPoint(0.25, 0.5),
                                         SPoint(0.5, 0.5)};



const int NumMineVerts = 4;
const SPoint mine[NumMineVerts] = {SPoint(-1, -1),
                                   SPoint(-1, 1),
                                   SPoint(1, 1),
                                   SPoint(1, -1)};


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the mines and applies the
//	world transform to each vertex in the vertex buffer passed to this
//	method.
//-------------------------------------------------------------------
void CController::WorldTransform(vector<SPoint> &VBuffer, SVector2D vPos)
{
	//create the world transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(CParams::dMineScale, CParams::dMineScale);
	
	//translate
	matTransform.Translate(vPos.x, vPos.y);

	//transform the ships vertices
	matTransform.TransformSPoints(VBuffer);
}

//------------------------------------Render()--------------------------------------
//
//----------------------------------------------------------------------------------
void CController::Render(HDC surface)
{
	//render the stats
	string s = "Generation:          " + itos(m_iGenerations);
	TextOut(surface, 5, 0, s.c_str(), s.size());

	//do not render if running at accelerated speed
	if (!m_bFastRender)
	{
		//keep a record of the old pen
     m_OldPen = (HPEN)SelectObject(surface, m_GreenPen);

    //render the mines
		for (int i=0; i<m_NumMines; ++i)
		{
			//grab the vertices for the mine shape
			vector<SPoint> mineVB = m_MineVB;

			WorldTransform(mineVB, m_vecMines[i]);

			//draw the mines
			MoveToEx(surface, (int)mineVB[0].x, (int)mineVB[0].y, NULL);

			for (int vert=1; vert<mineVB.size(); ++vert)
			{
				LineTo(surface, (int)mineVB[vert].x, (int)mineVB[vert].y);
			}

			LineTo(surface, (int)mineVB[0].x, (int)mineVB[0].y);
			
		}
       		
    //we want the fittest displayed in red
    SelectObject(surface, m_RedPen);

		//render the sweepers
		for (i=0; i<m_NumSweepers; i++)
		{
			if (i == CParams::iNumElite)
      {
        SelectObject(surface, m_OldPen);
      }
      
      //grab the sweeper vertices
			vector<SPoint> sweeperVB = m_SweeperVB;

			//transform the vertex buffer
			m_vecSweepers[i].WorldTransform(sweeperVB);

			//draw the sweeper left track
			MoveToEx(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y, NULL);

			for (int vert=1; vert<4; ++vert)
			{
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
			}

      LineTo(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y);

      //draw the sweeper right track
			MoveToEx(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y, NULL);

			for (vert=5; vert<8; ++vert)
			{
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
			}

      LineTo(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y);

      MoveToEx(surface, (int)sweeperVB[8].x, (int)sweeperVB[8].y, NULL);
      LineTo(surface, (int)sweeperVB[9].x, (int)sweeperVB[9].y);

      MoveToEx(surface, (int)sweeperVB[10].x, (int)sweeperVB[10].y, NULL);

      for (vert=11; vert<16; ++vert)
			{
				LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
			}

		}

    //put the old pen back
    SelectObject(surface, m_OldPen);

	}//end if

  else
  {
    PlotStats(surface);
  }
}


//--------------------------PlotStats-------------------------------------
//
//  Given a surface to draw on this function displays stats and a crude
//  graph showing best and average fitness
//------------------------------------------------------------------------
void CController::PlotStats(HDC surface)
{
    string s = "Best Fitness:       " + ftos(m_pGA->BestFitness());
	  TextOut(surface, 5, 20, s.c_str(), s.size());

     s = "Average Fitness: " + ftos(m_pGA->AverageFitness());
	  TextOut(surface, 5, 40, s.c_str(), s.size());
    
    //render the graph
    float HSlice = (float)cxClient/(m_iGenerations+1);
    float VSlice = (float)cyClient/((m_pGA->BestFitness()+1)*2);

    //plot the graph for the best fitness
    float x = 0;
    
    m_OldPen = (HPEN)SelectObject(surface, m_RedPen);

    MoveToEx(surface, 0, cyClient, NULL);
    
    for (int i=0; i<m_vecBestFitness.size(); ++i)
    {
       LineTo(surface, x, cyClient - VSlice*m_vecBestFitness[i]);

       x += HSlice;
    }

    //plot the graph for the average fitness
    x = 0;

    SelectObject(surface, m_BluePen);

    MoveToEx(surface, 0, cyClient, NULL);
    
    for (i=0; i<m_vecAvFitness.size(); ++i)
    {
       LineTo(surface, (int)x, (int)(cyClient - VSlice*m_vecAvFitness[i]));

       x += HSlice;
    }

    //replace the old pen
    SelectObject(surface, m_OldPen);
}
