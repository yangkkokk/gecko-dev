/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are Copyright (C) 1998
 * Netscape Communications Corporation.  All Rights Reserved.
 */
#ifndef nsFrameReflowState_h___
#define nsFrameReflowState_h___

#include "nsIFrame.h"

struct nsStyleDisplay;
struct nsStyleSpacing;
struct nsStyleText;

class nsFrameReflowState : public nsReflowState {
public:
  nsFrameReflowState(nsIPresContext& aPresContext,
                     const nsReflowState& aReflowState,
                     const nsReflowMetrics& aMetrics);
  ~nsFrameReflowState();

  nsIPresContext& mPresContext;
  nsIFrame* mNextRCFrame;

  PRBool mComputeMaxElementSize;
  nsSize mMaxElementSize;

  // Style data pointers for frame
  const nsStyleText* mStyleText;
  const nsStyleDisplay* mStyleDisplay;
  const nsStyleSpacing* mStyleSpacing;

  // This is true if no-wrap is set for frame
  PRBool mNoWrap;

  // This direction of reflow (left to right, right to left)
  PRUint8 mDirection;

  // The area to reflow within that includes the frames border and
  // padding. Because it contains everything, the x/y values are known
  // to be zero. The width/height may be NS_UNCONSTRAINEDSIZE if the
  // container reflowing this frame has given the frame an
  // unconstrained area.
  //
  // Note: This is not initialized by the constructor; derived classes
  // must initialize this field.
  nsSize mBorderArea;

  // The content area to reflow child frames within. The x/y
  // coordinates are known to be mBorderPadding.left and
  // mBorderPadding.top. The width/height may be NS_UNCONSTRAINEDSIZE
  // if the container reflowing this frame has given the frame an
  // unconstrained area.
  //
  // Note: This is not initialized by the constructor; derived classes
  // must initialize this field.
  nsSize mContentArea;

  // The frames border+padding value
  nsMargin mBorderPadding;

  // The running margin value. This value is a copy of
  // nsReflowMetrics.mCarriedInTopMargin before the first frame is
  // reflowed, and after a frame is reflowed and placed it will be the
  // collapsed bottom margin value from the frame.
  nscoord mRunningMargin;
};

#endif /* nsFrameReflowState_h___ */
