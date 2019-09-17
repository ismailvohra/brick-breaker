#include"Board.h"
#include"Statics.h"
#include"Brick.h"
#include"Point.h"
#include<SDL.h>
#include<iostream>
#include<ostream>

using namespace std;

Board::Board()
{
    head = NULL;
    tail = NULL;
}
Board::Board(float x, float y, float width, float height, SDL_Renderer* renderer)
{
    head = NULL;
    tail = NULL;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->renderer = renderer;
    if(!loadMedia()){
        std::cout<<"Error loading media in Board class";
    }
}

Board::~Board()
{
    while(head != NULL)
    {
        Node* temp = head;
        head = head->next;
        //cout<<"Deallocating value: "<<temp->data<<endl;
        delete temp;
    }
    this->brickSpriteSheet.Free();
}

void Board::Enqueue(Brick* brick, int column, int row)
{
    if(head == NULL)
    {
        head = new Node;
        head->brick = brick;
        head->position = column;
        head->y = row;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
    }
    else
    {
        tail->next = new Node;
        tail->next->position = column;
        tail->next->y = row;
        tail->next->brick = brick;
        tail->next->next = NULL;
        tail->next->prev = tail;
        tail = tail->next;
    }
}

/*

Brick* Board::Dequeue()
{
    int value = -1;
    if(head != NULL)
    //Brick* brick;
    {
        Brick* brick;
        Node* temp = head;
        brick = head->brick;
        head = head->next;
        if(head!=NULL)
        {
            head->prev = NULL;
        }
        return brick;
        delete temp;
    }
}
*/
bool flag = true;
void Board::Display(SDL_Renderer* gRenderer)
{
    // Render bricks
    Node* temp = head;
    if(flag){
        flag = false;
        cout<<gRenderer<<endl;
    }
    while(temp!=NULL){

        Brick brick = *temp->brick;
        int i= temp->position;
        int j = temp->y;

        temp = temp->next;

        // Check if the brick exists
        if(!brick.state)
        {
            continue;
        }


        SDL_Rect srcrect;
        srcrect.x = 7 + (brick.type * BOARD_BRWIDTH);
        if(brick.breaktype==3)
        {
            srcrect.y = 59 + ((0) * BOARD_BRHEIGHT);
        }
        else{
            srcrect.y = 59 + ((brick.breaktype) * BOARD_BRHEIGHT);
        }
        srcrect.w = BOARD_BRWIDTH;
        srcrect.h = BOARD_BRHEIGHT;

        SDL_Rect dstrect;
        dstrect.x = x + (i * BOARD_BRWIDTH);
        dstrect.y = y + (j * BOARD_BRHEIGHT);
        dstrect.w = BOARD_BRWIDTH;
        dstrect.h = BOARD_BRHEIGHT;

        brickSpriteSheet.Render(dstrect.x,dstrect.y,&srcrect,0.0,NULL,SDL_FLIP_NONE,gRenderer);
    }
}
bool Board::loadMedia()
{
	//Load sprite sheet texture
	if( !brickSpriteSheet.LoadFromFile( "Images/finalsprites.png", renderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
        return false;
	}
	return true;
}
CollisionInfo Board::detectCollisionWithBricks(Point ballPos, BallType ballType, Point ballSize){
    Node* temp = head;
    CollisionInfo c;
    while(temp!=NULL){
        CollisionType type = detectCollisionWithBrick(ballPos, ballSize, temp);
        if(type != None){
            c.directionType = type;
            c.objectType = temp->brick->type == 3 ? CollisionObjectUnbreakableBrickType : CollisionObjectBreakableBrickType;
            c.brick = removeBrickAt(temp, ballType);
            return c;
        }
        temp = temp->next;
    }
    c.directionType = None;
    c.objectType = CollisionObjectBreakableBrickType;
    return c;
}
bool Board::detectCollisionWithBricks(Point firePos, FireType fireType){
    Node* temp = head;
    while(temp!=NULL){
        bool didCollide = detectCollisionWithBrick(firePos, temp);
        if(didCollide){
            removeBrickAt(temp, fireType);
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int previousX = -1;
int previousY = -1;
CollisionType Board::detectCollisionWithBrick(Point objectPos, Point objectSize, Node* brickNode){
    int i = brickNode->position;
    int j = brickNode->y;
    if(!brickNode->brick->state){
        return None;
    }
    Point brickPos(x + (i * BOARD_BRWIDTH), y + (j * BOARD_BRHEIGHT));
    Point brickDestPoint(brickPos.x + BOARD_BRWIDTH, brickPos.y + BOARD_BRHEIGHT);
    Point objectDestPoint(objectPos.x + objectSize.x, objectPos.y + objectSize.y);
    Point objectCenterPoint((objectPos.x + objectPos.x + objectSize.x)/2, (objectPos.y + objectPos.y + objectSize.y)/2);
    bool isInXRange = (brickPos.x <= objectPos.x && brickDestPoint.x >= objectCenterPoint.x) || (brickPos.x <= objectCenterPoint.x && brickDestPoint.x >= objectDestPoint.x);
    //Vertical Collision Detection
    if(isInXRange){
        bool didCollide = (brickPos.y > objectPos.y && brickPos.y < objectDestPoint.y) || (brickDestPoint.y > objectPos.y && brickDestPoint.y < objectDestPoint.y);
        if(didCollide && previousX == i && previousY == j){
            cout<<"Ball collided to brick of position("<<i<<","<<j<<") and ball origin ("<<objectPos.x<<","<<objectPos.y<<")"<<endl;
        }
        previousX = i;
        previousY = j;
        return didCollide ? Vertical : None;
    }
    //Horizontal Collision Detection
    bool isInYRange = (brickPos.y <= objectPos.y && brickDestPoint.y >= objectCenterPoint.y) || (brickPos.y <= objectCenterPoint.y && brickDestPoint.y >= objectDestPoint.y);
    if(isInYRange){
        bool didCollide = (brickPos.x > objectPos.x && brickPos.x < objectDestPoint.x) || (brickDestPoint.x > objectPos.x && brickDestPoint.x < objectDestPoint.x);
        if(didCollide && previousX == i && previousY == j){
            cout<<"Ball collided to brick of position("<<i<<","<<j<<") and ball origin ("<<objectPos.x<<","<<objectPos.y<<")"<<endl;
        }
        previousX = i;
        previousY = j;
        return didCollide ? Horizontal : None;
    }
    return None;
}
bool Board::detectCollisionWithBrick(Point firePos, Node* brickNode){
    int i = brickNode->position;
    int j = brickNode->y;
    if(!brickNode->brick->state){
        return None;
    }
    Point brickPos(x + (i * BOARD_BRWIDTH), y + (j * BOARD_BRHEIGHT));
    Point brickDestPoint(brickPos.x + BOARD_BRWIDTH, brickPos.y + BOARD_BRHEIGHT);

    bool isInXRange = (brickPos.x <= firePos.x && brickDestPoint.x >= firePos.x);
    if(!isInXRange){

    }
    return isInXRange && (brickDestPoint.y > firePos.y);
}
Node* Board::getHead(){
    return head;
}
Brick* Board::removeBrickAt(Node* node, BallType balltype)
{
    bool shouldDelete = false;
    if(balltype==NormalBallType)
    {

        if(node->brick->type!=3)
        {
            if(node->brick->breaktype==0)
            {
                shouldDelete = true;
            }else{
                node->brick->breaktype-- ;
            }
        }
    }
    else if(balltype==FireBallType)
    {
        shouldDelete = true;
        if(node->prev)
        {
            if(node->position-node->prev->position==1)
            {
                lowerbricktype(node->prev);
            }
        }
        if(node->next)
        {
            if(node->position-node->next->position==-1)
            {
                lowerbricktype(node->next);
            }
        }
        Node* temp = accessat(node->position, (node->y)-1);
        if(temp)
        {
            lowerbricktype(temp);
        }
        temp = accessat(node->position+1, (node->y)-1);
        if(temp)
        {
            lowerbricktype(temp);
        }
        temp = accessat(node->position-1, (node->y)-1);
        if(temp)
        {
            lowerbricktype(temp);
        }
        temp = accessat(node->position, (node->y)+1);
        if(temp)
        {
            lowerbricktype(temp);
        }
        temp = accessat(node->position-1, (node->y)+1);
        if(temp)
        {
            lowerbricktype(temp);
        }
        temp = accessat(node->position+1, (node->y)+1);
        if(temp)
        {
            lowerbricktype(temp);
        }
    }
    else if(balltype==ThroughBallType)
    {
        shouldDelete = node->brick->type!=3;
    }
    if(shouldDelete){
        node->brick->state = false;
        if(node->next){
            node->next->prev =  node->prev;
        }
        if(node->prev)
        {
            node->prev->next = node->next;
        }
        if(node == head){
            head = node->next;
        }
        if(node == tail){
            tail = node->prev;
        }
        Brick* brick = node->brick;
        delete node;
        return brick;
    }
    return NULL;
}
Node* Board::accessat(int i, int j)
{
    Node* temp=head;
    while(temp!=NULL)
    {
        if(temp->position==i && temp->y==j)
        {
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
void Board::lowerbricktype(Node* node)
{
    if(node->brick->type != 3 && node->brick->breaktype!=0)
    {
        node->brick->breaktype--;
    }
    else if(node->brick->breaktype==0)
    {
        node->brick->state=false;
        if(node->next){
            node->next->prev =  node->prev;
        }
        if(node->prev)
        {
            node->prev->next = node->next;
        }
        if(node == head){
            head = node->next;
        }
        if(node == tail){
            tail = tail->prev;
        }
        Brick* brick = node->brick;
        delete node;
        delete brick;
    }
}
Brick* Board::removeBrickAt(Node* node, FireType firetype)
{
    if(firetype==NormalFireType)
    {
        lowerbricktype(node);
        return node->brick;
    }
    if(firetype==MissileFireType)
    {
        return removeBrickAt(node, FireBallType);
    }
    return NULL;
}
bool Board::isLevelComplete(){
    Node* temp=head;
    while(temp!=NULL)
    {
        if(temp->brick->state && temp->brick->type != 3)
        {
            return false;
        }
        temp=temp->next;
    }
    return true;
}
