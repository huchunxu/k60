/*
 * =====================================================================================
 *        COPYRIGHT NOTICE
 *        Copyright (c) 2012  HUST-Renesas Lab
 *        ALL rights reserved.
 *//**        
 *        @file     image_process.c
 *
 *        @brief    图像处理
 *
 *        @version  0.1
 *        @date     2012/5/15  19：58
 *
 *        @author   Hu Chunxu , hcx196@gmail.com
 *//* ==================================================================================
 *  @0.1    Hu Chunxu   2012/5/15    create orignal file
 * =====================================================================================
 */
#include <stdio.h>

#include "image_process.h"
#include "arm_math.h"
#include "sd.h"
#include "ff.h"


/**
 * compress image涉及全局变量
 */

volatile int gl_SRNum = 0;             /*  active point */
volatile static int gl_compresXLast = 0, compresXHead = 0, gl_compresYLast = 0;
volatile static int gl_X = 0, gl_Y = 0;
volatile image_road_startline StrRoadFind[STR_ROAD_MAX_NUM+1] = {{0,0,0}};

/**
 * find road涉及全局变量
 */
volatile uint8_t gl_road[MAX_Y];            /*最后找到的路*/
volatile uint8_t gl_lastRoad[MAX_Y];        /*上周期的路*/

volatile uint8_t gl_lastRoadStartY = 10;    /*上周期的路的起点*/
volatile uint8_t gl_lastRoadEndY   = 60;    /*上周期的路的终点*/

volatile uint8_t gl_roadStartY = 10;        /*路的起点*/
volatile uint8_t gl_roadEndY   = 60;        /*路的终点*/
volatile uint32_t gl_motherRoadLen;         /*母路的长度*/

uint8_t gl_noway_flag;                       /*有无路的标志*/

char_t buffer[12800];        /* file copy buffer, 1k bytes */

const unsigned char STR_MAX_Width[128] 
     = {30,30,30,30,30,30,30,30,30,30,
        30,30,30,30,30,30,30,30,30,30,
        30,30,29,29,28,28,27,27,26,26,
        25,25,25,25,25,24,24,24,24,24,
        23,23,23,23,23,22,22,22,22,22,
        21,21,21,21,21,20,20,20,20,20,
        19,19,19,19,19,18,18,18,18,18,
        17,17,17,17,17,16,16,16,16,16,
        15,15,15,15,15,14,14,14,14,14,
        13,13,13,13,13,12,12,12,12,12,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
         0, 0, 0, 0, 0, 0, 0, 0};     

/*路宽的最大宽度*/
const uint8_t road_max_width[MAX_Y] = 
       {40, 40, 40, 40, 40, 40, 40, 40, 40, 40,
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 
        40, 40, 40, 40, 40, 40, 40, 40, 40, 40};



static uint8_t Step_Y_S(void);
static uint8_t Step_Y_E(void);
static uint8_t MyAbs_ItC(int32_t number);
static int MyAbs_ItI(int number);

/**
 *    @brief   压缩图像
 */
void compress_image(void)
{    
    static int AbsValue = 0;
    int         buf_num = 12800; 
    int         value_temp = 0;
    uint32_t    block_size = 1;

    gl_SRNum = 0;
    gl_compresXLast = 0;
    gl_compresYLast = 0;
    compresXHead = 0;
    gl_X = 0;
    gl_Y = 0;  
    
    for(buf_num = 12800; buf_num > 0; buf_num--)
    {
         /* update the points information  */
        gl_compresXLast = gl_X;
        gl_compresYLast = gl_Y;

        /*  read the points' coordinate  */
        if(buffer[buf_num] == 0)
        {
            gl_X = buf_num % 128;
            //arm_shift_q31(&buf_num, -7, &value_temp, block_size);
            //gl_Y = 100 - value_temp;
            gl_Y = 100 - buf_num / 128;
        }
        
       /*  compress the effective points */
        //if ((gl_Y>2) && (gl_X < 128) && (gl_SRNum < STR_ROAD_MAX_NUM))
        if (gl_SRNum < STR_ROAD_MAX_NUM)
        {
            AbsValue = MyAbs_ItI(gl_X - gl_compresXLast);
            //value_temp = gl_X - gl_compresXLast;
            //arm_abs_q31(&value_temp, &AbsValue, block_size);

            if (((AbsValue > CONTINUE_VALUE) && (gl_Y == gl_compresYLast))
                    || (gl_Y > gl_compresYLast))
            {
                if ((gl_compresXLast != compresXHead) 
                        && ((gl_compresXLast- compresXHead) < STR_MAX_Width[gl_compresYLast])
                        && (compresXHead > 2)
                        && (compresXHead < 118))  /* the road condition   */
                {
                    StrRoadFind[gl_SRNum].CenterX
                            = (unsigned char) ((gl_compresXLast + compresXHead) >> 1);
                    StrRoadFind[gl_SRNum].CenterY = (unsigned char)gl_compresYLast;
                    StrRoadFind[gl_SRNum].Width
                            = (unsigned char) (compresXHead - gl_compresXLast);
                    gl_SRNum++;
                }
                 /* the next road's beganing point  */
                compresXHead = gl_X;
            }
        } /* end if(gl_X < 194)  */
    }/*  end while((gl_frameEndFlag == 0) && (earlyFlag == 0)) */
}


/**
 *    @brief   取绝对值（int-->int）
 *
 *    @param   number  需要取绝对值的原始值
 *
 *    @return  ret  绝对值
 */
static int MyAbs_ItI(int number)
{
    int ret = 0;
    
    if(number < 0)
    {
      number = 0 - number; 
    }            
    ret = number;
    
    return ret;
}


/**
 *    @brief   找路
 */
ER find_road(void)
{
    /* init */
    image_road    LineXY[MAX_LINE_POINT];
    uint8_t Start[MAX_LINE] = {0};
    uint8_t End[MAX_LINE] = {0};
    uint8_t LengthStack[MAX_LINE] = {0};
    uint8_t finalLine = 0;
    int8_t lastK = 0;
    int8_t lineK = 0;
    uint8_t linePoint = 0;
    uint8_t addStepY = 0;
    volatile uint8_t i = 0, k = 0;
    volatile uint32_t p = 0;
    uint8_t saveFlag = 0;
    uint8_t lastStartY = 0;
    uint8_t lineLength = 0;
    int8_t lineWidth = 0;
    int32_t expectFinalX = 0;
    uint8_t AbsValue = 0;

    for (i = 0; i < MAX_LINE_POINT; i++)
    {
        LineXY[i].CenterX = 255;
        LineXY[i].CenterY = 255;
    }
    for (i = 0; i < MAX_Y; i++)
    {
        gl_road[i] = 255;
    }
    for (i = 0; i < MAX_LINE; i++)
    {
        Start[i] = 255;
        End[i] = 0;
        LengthStack[i] = 0;
    }

    linePoint = 0;
    saveFlag = 0;

    /*find the child gl_road*/
    for (i = 0; i < MAX_LINE; i++) /* searching times = MAX_LINE */
    {
        for (p = 0; p < gl_SRNum; p++)
        {
            /*protection*/
            if (linePoint > (MAX_LINE_POINT - 2))
            {
                break;
            }
            if (StrRoadFind[p].Width > road_max_width[StrRoadFind[p].CenterY])
            {
                continue;
            }
            if ((int)StrRoadFind[p].CenterX == 1)
            {
                continue;
            }

            /*rememer the start point*/
            if (Start[i] == 255)
            {
                lastK = 0;
                Start[i] = linePoint;
                LineXY[linePoint].CenterX = StrRoadFind[p].CenterX;
                LineXY[linePoint].CenterY = StrRoadFind[p].CenterY;
                StrRoadFind[p].Width += 100; /* make flag */
                saveFlag = 1;            
            }
            else if ((StrRoadFind[p].CenterY - LineXY[linePoint].CenterY)> SKIP_LINE)
            {
                break;
            }
            else
            {
                if (LineXY[linePoint].CenterY == StrRoadFind[p].CenterY) /* everyline only one point */
                {
                    continue;
                }
                AbsValue = MyAbs_ItC( (int32_t) StrRoadFind[p].CenterX
                                - ((int32_t) LineXY[linePoint].CenterX
                                        + (int32_t) lastK));
                if (AbsValue <= MAX_K)
                {
                    lastK = (StrRoadFind[p].CenterX
                                    - LineXY[linePoint].CenterX);
                    StrRoadFind[p].Width += 100;
                    linePoint++;
                    LineXY[linePoint].CenterX = StrRoadFind[p].CenterX;
                    LineXY[linePoint].CenterY = StrRoadFind[p].CenterY;
                    saveFlag = 1;
                    
                }
            }
        } /* end for(p=0;p<=effectivePoint;p++) */

        /* protection */
        if ((linePoint > (MAX_LINE_POINT - 2)) || (saveFlag == 0))
        {
            break;
        }

        /*reset the flag*/
        saveFlag = 0;
        End[i] = linePoint;
        LengthStack[i] = LineXY[End[i]].CenterY - LineXY[Start[i]].CenterY;
        linePoint++;

        /*recall the space of the */
        if (LengthStack[i] < CONTINUE_LINE)
        {
            for (k = Start[i]; k <= End[i]; k++)
            {
                LineXY[k].CenterX = 255;
                LineXY[k].CenterY = 255;
            }
            LengthStack[i] = 0;
            linePoint = Start[i];
            Start[i] = 255;
            End[i] = 0;
            i--;
        }
        
//        for(p=Start[i];p<End[i];p++)
//        printf("%d\t%d\n\r",(int)LineXY[p].CenterX,(int)LineXY[p].CenterY);
    } /* end  for (i=0;i<MAX_LINE;i++) */
    saveFlag = 0;
    
    /*the longest child gl_road is the mother gl_road*/
//   for (k = 1; k < MAX_LINE; k++)
//   {
//       if (LengthStack[finalLine] < LengthStack[k])
//       {
//           finalLine = k;
//       }
//   }
    arm_max_q7(LengthStack, MAX_LINE, &gl_motherRoadLen, &finalLine);
 
    gl_motherRoadLen = End[finalLine] - Start[finalLine];
    
    /*  noway  */
    if (gl_motherRoadLen < 10)
    {
        gl_noway_flag = 1;
    }

    /*  contact the child gl_road  */
    else
    {
        gl_noway_flag = 0;
        for (i = Start[finalLine]; i <= End[finalLine]; i++)
        {
            gl_road[LineXY[i].CenterY] = LineXY[i].CenterX;
        }
        gl_roadStartY = LineXY[Start[finalLine]].CenterY; /*  the startY and endY of the gl_road  */
        gl_roadEndY = LineXY[End[finalLine]].CenterY;

        /*contact the child road that is near*/
        addStepY = Step_Y_S(); /*  the step of the mother road  */

        for (k = 0; k < MAX_LINE; k++)
        {
            if ((Start[k] == 255) || (LineXY[End[k]].CenterY > gl_roadStartY)
                    || (k == finalLine))
            {
                continue;
            }
            if (saveFlag == 1)
            {
                addStepY = Step_Y_S();
                saveFlag = 0;
            }
            lineK = (int32_t) gl_road[gl_roadStartY] - (int32_t) gl_road[addStepY];

            /* find the expectFinalX */
            expectFinalX = (uint8_t) (((int32_t) LineXY[End[k]].CenterY
                    - (int32_t) gl_roadStartY) * lineK / ((int32_t) gl_roadStartY
                    - (int32_t) addStepY) + (int32_t) gl_road[gl_roadStartY]);

            AbsValue = MyAbs_ItC(
                    (int32_t) LineXY[End[k]].CenterX - (int32_t) expectFinalX);
            if ((AbsValue < road_max_width[End[k]]) && (expectFinalX > 0)
                    && (expectFinalX < MAX_X))
            {
                lineLength = (int32_t) gl_roadStartY - (int32_t) LineXY[End[k]].CenterY;
                lineWidth = (int32_t) gl_road[gl_roadStartY]
                        - (int32_t) LineXY[End[k]].CenterX;
                for (i = LineXY[End[k]].CenterY + 1; i < gl_roadStartY; i++)
                {
                    gl_road[i] = (uint8_t) (((int32_t) i
                            - (int32_t) LineXY[End[k]].CenterY) * lineWidth
                            / lineLength + (int32_t) LineXY[End[k]].CenterX);
                }
                for (i = Start[k]; i <= End[k]; i++)
                {
                    gl_road[LineXY[i].CenterY] = LineXY[i].CenterX;
                }
                gl_roadStartY = LineXY[Start[k]].CenterY;
                LengthStack[finalLine] += LengthStack[k];
                saveFlag = 1;

            } /* end if((AbsValue < road_max_width[End[k]] ) */
        } /* end for (i = 0; i < MAX_LINE; i++) */

        /* contact the child road that is faraway */
//        addStepY = Step_Y_E();
//        saveFlag = 0;
//
//        for (k = 0; k < MAX_LINE; k++)
//        {
//            if ((Start[k] == 255) || (LineXY[Start[k]].CenterY < gl_roadEndY)
//                    || ((LineXY[Start[k]].CenterY - gl_roadEndY) > 30))
//            {
//                continue;
//            }
//            if (saveFlag == 1)
//            {
//                addStepY = Step_Y_E();
//                saveFlag = 0;
//            }
//
//            lineK = (int32_t) gl_road[gl_roadEndY] - (int32_t) gl_road[addStepY];
//            expectFinalX = (uint8_t) (((int32_t) LineXY[Start[k]].CenterY
//                    - (int32_t) gl_roadEndY) * lineK / ((int32_t) gl_roadEndY
//                    - (int32_t) addStepY) + (int32_t) gl_road[gl_roadEndY]);
//
//            AbsValue = MyAbs_ItC(
//                    (int32_t) LineXY[Start[k]].CenterX - (int32_t) expectFinalX);
//
//            if (AbsValue < road_max_width[End[k]] && (expectFinalX > 0)
//                    && (expectFinalX < MAX_X))
//            {
//                lineLength = (int32_t) LineXY[Start[k]].CenterY - (int32_t) gl_roadEndY;
//                lineWidth = (int32_t) LineXY[Start[k]].CenterX
//                        - (int32_t) gl_road[gl_roadEndY];
//                for (i = gl_roadEndY + 1; i < LineXY[Start[k]].CenterY; i++)
//                {
//                    gl_road[i] = (uint8_t) (((int32_t) i - (int32_t) gl_roadEndY)
//                            * lineWidth / lineLength + (int32_t) gl_road[gl_roadEndY]);
//                }
//                for (i = Start[k]; i <= End[k]; i++)
//                {
//                    gl_road[LineXY[i].CenterY] = LineXY[i].CenterX;
//                }
//                gl_roadEndY = LineXY[End[k]].CenterY;
//                LengthStack[finalLine] += LengthStack[k];
//                saveFlag = 1;
//            }/* end if (MyAbs(LineXY[End[i]].CenterX - expectFinalX) < road_max_width[LineXY[End[i]].CenterY]) */
//        }/* end for (i = 0; i < MAX_LINE; i++) */

        /* make the road to the nearest side */
        if ((gl_roadStartY > 0) && (gl_road[gl_roadStartY] < 128))
        {
            lastStartY = gl_roadStartY;
            addStepY = Step_Y_S();
            lineLength = (int32_t) addStepY - (int32_t) lastStartY;
            lineWidth = (int32_t) gl_road[lastStartY] - (int32_t) gl_road[addStepY];
            while (gl_roadStartY > 0)
            {
                gl_roadStartY--;
                gl_road[gl_roadStartY] = (uint8_t) (((int32_t) lastStartY
                        - (int32_t) gl_roadStartY) * lineWidth / lineLength
                        + (int32_t) gl_road[lastStartY]);
                if ((gl_road[gl_roadStartY] > (MAX_X - 5)) || (gl_road[gl_roadStartY] < 5)) //space reback
                {
                    if ((gl_road[gl_roadStartY] > MAX_X) && (gl_road[gl_roadStartY]
                            < 255))
                    {
                        gl_road[gl_roadStartY] = 255;
                        gl_roadStartY++;
                    }
                    break;
                }
            } /* end while (gl_roadStartY > 0) */
        } /* end else if (gl_roadStartY > 1 && gl_road[gl_roadStartY] >= 10 && gl_road[gl_roadEndY] <= 180) */
    }/* end else */
    
    BeautifyRoad();
    
//    for(p = gl_roadStartY; p<gl_roadEndY; p++)
//    {
//        printf("%d\t%d\n\r",(int)gl_road[p], p);
//    }
    
    return E_OK;
}


static uint8_t Step_Y_S(void)
{
    uint8_t stepStart;

    stepStart = gl_roadStartY + K_STEP_Y;

    if(stepStart > gl_roadEndY)
    {
        stepStart = gl_roadEndY;
    }

    while (gl_road[stepStart] == 255)
    {
        if(stepStart >= gl_roadEndY)
        {
             stepStart = gl_roadEndY;
             break;
        }
        stepStart++;
    }
    return stepStart;
}

static uint8_t Step_Y_E(void)
{
    uint8_t stepEnd;

    if(gl_roadEndY > 45)
    {
        stepEnd = gl_roadEndY - K_STEP_E;
    }
    else
    {
        stepEnd = gl_roadEndY - K_STEP_Y;
    }

    if(stepEnd < gl_roadStartY)
    {
        stepEnd = gl_roadStartY;
    }

    while (gl_road[stepEnd] == 255)
    {
        if(stepEnd <= gl_roadStartY)
        {
             stepEnd = gl_roadStartY;
             break;
        }
        stepEnd--;
    }
    return stepEnd;
}

static uint8_t MyAbs_ItC(int32_t number)
{
    uint8_t ret = 0;

    if(number < 0)
    {
      number = 0 - number;
    }
    ret = (uint8_t)number;

    return ret;
}

/**
 *    @brief   美化路径
 */
void BeautifyRoad(void)
{
    int i = 0, j = 0;
    int startPoint = 0;
      
    for(i=gl_roadStartY + 1; i<=gl_roadEndY; i++)
    {
       startPoint = i;
       while(gl_road[i] == 255)
       {
           i++;
       }
       for(j=startPoint;j<i;j++)
       {
           gl_road[j] = (unsigned char)(((int)gl_road[i]-(int)gl_road[j-1])/(i-j+1)) + gl_road[j-1]; 
       }
    }
}

