/***************************************************************************
                          rotary.h  -  description
                             -------------------
    begin                : Tue Sep 21 2004
    copyright            : (C) 2004 by Tue Haste Andersen
    email                : haste@diku.dk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ROTARY_H
#define ROTARY_H

#include <qthread.h>

/**
  * Virtual class for handling the PowerMate. This is implemented as a separate thread.
  *
  *@author Tue Haste Andersen
  */

class ControlObject;
class QTime;

const int kiRotaryFilterMaxLen = 25;
static QString kqRotaryMappingP1Phase =   "Player 1, phase adjustment";
static QString kqRotaryMappingP1Scratch = "Player 1, scratch";
static QString kqRotaryMappingP2Phase =   "Player 2, phase adjustment";
static QString kqRotaryMappingP2Scratch = "Player 2, scratch";

class Rotary : public QThread
{
public:
    Rotary();
    ~Rotary();

    /** Open a rotary device */
    virtual bool opendev(QString name) = 0;
    /** Close a rotary device */
    virtual void closedev() = 0;
    /** Wait for the next rotary event. Blocking call. */
    virtual void getNextEvent() = 0;
    /** Select mapping */
    void selectMapping(QString mapping);
    /** Start calibration measurement */
    void calibrateStart();
    /** End calibration measurement */
    double calibrateEnd();
    /** Set calibration */
    void setCalibration(double c);
protected:
    /** Main thread loop */
    virtual void run();
    /** Send out a low pass filtered rotary event */
    void sendRotaryEvent(double dValue);
    /** Send out a button event */
    void sendButtonEvent();
    /** Pointer to associated ControlObjects */
    ControlObject *m_pControlObjectRotary, *m_pControlObjectButton;
    /** Length of filter */
    int m_iFilterLength;
    /** Pointer to rotary filter buffer */
    double *m_pFilter;
    /** Calibration value */
    double m_dCalibration;
    /** Time used in calibration */
    QTime *m_pCalibrationTime;
};

#endif
