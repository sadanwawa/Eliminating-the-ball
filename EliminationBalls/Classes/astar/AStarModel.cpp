//
//  AStarModel.cpp
//  minGameTest
//
//  Created by 马 英臣 on 13-10-11.
//
//

#include "AStarModel.h"


// singleton instance pointer
template<> AStarModel* Singleton<AStarModel>::msSingleton	= NULL;

//插入openList合适位置
void AStarModel::insertInOpenSteps(StepVO* stepVO)
{
	int stepFScore = stepVO->getValueF(); 
	int count = _openList->count();
	int i = 0; 
	for (; i < count; i++) {        
		if (stepFScore <=dynamic_cast<StepVO*>(_openList->objectAtIndex(i))->getValueF()) {
			break;
		}
	}	        
    _openList->insertObject(stepVO, i);        
}

//计算估算值 当前位置  到目标位置
int AStarModel::computeHScoreFromCoord(Point currPoint,Point targetPoint)
{	
    return abs(targetPoint.x-currPoint.x)+fabsf(targetPoint.y-currPoint.x);	
}

int AStarModel::costToMoveFromStep(StepVO* fromStep,StepVO* toStep)
{
	return ((fromStep->point.x != toStep->point.x) && (fromStep->point.y!= toStep->point.y)) ? 14 : 10;
}

//通过位置(行列)取得当前节点
StepVO* AStarModel::getStepVOByGPoint(Point pt){
    
    return NULL;
}

bool AStarModel::checkInArea(Point pt){
    return  pt.x>=1&&pt.x<=totalRowNum&&pt.y>=1&&pt.y<=totalLineNum;
}

Array* AStarModel::getALLNextToWalkableStepVOs(StepVO* stepvo)
{	
    Array* arr=Array::create();    
    bool t = false;
    bool l = false;
    bool b = false;
    bool r = false;
	
    Point pt=stepvo->point;
    
    //Top
    Point p=Point(pt.x,pt.y+1);
    if(p.y<=totalLineNum&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
        t=true;
    }
    
    //Left
    p=Point(pt.x-1,pt.y);
    if(p.x>=1&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
        l=true;
    }
    
    //Bottom
    p=Point(pt.x,pt.y-1);
    if(p.y>=1&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
        b=true;
    }
	
	// Right
    p=Point(pt.x+1,pt.y);
    if(p.x<=totalRowNum&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
        r=true;
    }
    
    // Top Left
    p=Point(pt.x-1,pt.y+1);
    if(t && l && checkInArea(p)&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));       
    }
    
	//  Bottom Left
    p=Point(pt.x-1,pt.y-1);
    if(b && l && checkInArea(p)&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
    }
	
	// Top Right
	p=Point(pt.x+1,pt.y+1);
    if(t && r && checkInArea(p)&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
    }
		
	// Bottom Right
    p=Point(pt.x+1,pt.y-1);
    if(b && r && checkInArea(p)&&stepvo->isWalkAble){
        arr->addObject(getStepVOByGPoint(p));
    }
         
	return arr;
}


bool AStarModel::searchPathByPoint(Point pointA,Point pointB){

    _openList=Array::create();
    _closeList=Array::create();
    _shortPath="";
    
/*
    // Init shortest path properties
	self.spOpenSteps = [NSMutableArray array];
	self.spClosedSteps = [NSMutableArray array];
	self.shortestPath = nil;
	
    
    
    
    
	// Get current tile coordinate and desired tile coord
	CGPoint fromTileCoor = [_layer tileCoordForPosition:self.position];
    CGPoint toTileCoord = [_layer tileCoordForPosition:target];
	
	// Check that there is a path to compute ;-)
	if (CGPointEqualToPoint(fromTileCoor, toTileCoord)) {
		return;
	}
	
	// Must check that the desired location is walkable
	// In our case it's really easy, because only wall are unwalkable
    if ([_layer isWallAtTileCoord:toTileCoord]) {
        currentPlayedEffect = [[SimpleAudioEngine sharedEngine] playEffect:@"hitWall.wav"];
		return;
    }
	
	// Start by adding the from position to the open list
	[self insertInOpenSteps:[[[ShortestPathStep alloc] initWithPosition:fromTileCoor] autorelease]];
	
	do {
		// Get the lowest F cost step
		// Because the list is ordered, the first step is always the one with the lowest F cost
		ShortestPathStep *currentStep = [self.spOpenSteps objectAtIndex:0];
        
		// Add the current step to the closed set
		[self.spClosedSteps addObject:currentStep];
        
		// Remove it from the open list
		// Note that if we wanted to first removing from the open list, care should be taken to the memory
		[self.spOpenSteps removeObjectAtIndex:0];
		
		// If the currentStep is at the desired tile coordinate, we have done
		if (CGPointEqualToPoint(currentStep.position, toTileCoord)) {
			[self constructPathAndStartAnimationFromStep:currentStep];
			self.spOpenSteps = nil; // Set to nil to release unused memory
			self.spClosedSteps = nil; // Set to nil to release unused memory
			break;
		}
		
		// Get the adjacent tiles coord of the current step
		NSArray *adjSteps = [_layer walkableAdjacentTilesCoordForTileCoord:currentStep.position];
		for (NSValue *v in adjSteps) {
            
			ShortestPathStep *step = [[ShortestPathStep alloc] initWithPosition:[v CGPointValue]];
			
			// Check if the step isn't already in the closed set
			if ([self.spClosedSteps containsObject:step]) {
				[step release]; // Must releasing it to not leaking memory ;-)
				continue; // Ignore it
			}
			
			// Compute the cost form the current step to that step
			int moveCost = [self costToMoveFromStep:currentStep toAdjacentStep:step];
			
			// Check if the step is already in the open list
			NSUInteger index = [self.spOpenSteps indexOfObject:step];
			
			if (index == NSNotFound) { // Not on the open list, so add it
				
				// Set the current step as the parent
				step.parent = currentStep;
                
				// The G score is equal to the parent G score + the cost to move from the parent to it
				step.gScore = currentStep.gScore + moveCost;
				
				// Compute the H score which is the estimated movement cost to move from that step to the desired tile coordinate
				step.hScore = [self computeHScoreFromCoord:step.position toCoord:toTileCoord];
				
				// Adding it with the function which is preserving the list ordered by F score
				[self insertInOpenSteps:step];
				
				// Done, now release the step
				[step release];
			}
			else { // Already in the open list
				
				[step release]; // Release the freshly created one
				step = [self.spOpenSteps objectAtIndex:index]; // To retrieve the old one (which has its scores already computed ;-)
				
				// Check to see if the G score for that step is lower if we use the current step to get there
				if ((currentStep.gScore + moveCost) < step.gScore) {
					
					// The G score is equal to the parent G score + the cost to move from the parent to it
					step.gScore = currentStep.gScore + moveCost;
					
					// Because the G Score has changed, the F score may have changed too
					// So to keep the open list ordered we have to remove the step, and re-insert it with
					// the insert function which is preserving the list ordered by F score
					
					// We have to retain it before removing it from the list
					[step retain];
					
					// Now we can removing it from the list without be afraid that it can be released
					[self.spOpenSteps removeObjectAtIndex:index];
					
					// Re-insert it with the function which is preserving the list ordered by F score
					[self insertInOpenSteps:step];
					
					// Now we can release it because the oredered list retain it
					[step release];
				}
			}
		}
		
	} while ([self.spOpenSteps count] > 0);
	
	if (self.shortestPath == nil) { // No path found
		currentPlayedEffect = [[SimpleAudioEngine sharedEngine] playEffect:@"hitWall.wav"];
	}
*/        
    return true;
}

