//
//  Side.h
//  Project3
//
//  Created by Jonathan Woong on 5/11/14.
//  Copyright (c) 2014 Jonathan Woong. All rights reserved.
//

#ifndef Project3_Side_h
#define Project3_Side_h

enum Side { NORTH, SOUTH };

inline
Side opponent(Side s)
{
    return Side(1 - s);
}

#endif
