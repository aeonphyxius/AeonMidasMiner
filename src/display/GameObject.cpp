#include "GameObject.h"

GameObject::GameObject() :
	isvisible(true),
	position(glm::vec3(0, 0, 0)),
	scale(glm::vec3(1.f, 1.f, 1.f)),
	rotation(0),
	parent(nullptr)
{

}

GameObject::GameObject(bool par_isvisible, glm::vec3 par_position, float par_rotation, glm::vec3 par_scale) :
	isvisible(par_isvisible),
	position(par_position),
	scale(par_scale),
	rotation(par_rotation),
	parent(nullptr)
{
}
GameObject::~GameObject(){
	parent = nullptr;

	/*for (auto child : childs_list){
		delete child;
	}*/
	childs_list.clear();
}

void GameObject::addChild(GameObject* par_child)
{
	if (par_child->parent){
		par_child->parent->removeChild(par_child);
	}

	par_child->parent = this;
	childs_list.push_back(par_child);

}

void GameObject::removeChild(GameObject* par_child){
	if (par_child)
	{
		auto index = 0;
		for (auto child : childs_list){
			if (child == par_child){
				childs_list.erase(childs_list.begin() + index);
			}
		}		
	}
}

bool GameObject::isPointInside(const glm::vec2 *par_point) const{

	if (par_point->x >= getPosition().x &&
		par_point->x < getSize().x + getPosition().x &&
		par_point->y >= getPosition().y &&
		par_point->y < getSize().y + getPosition().y){

		return true;
	}

	return false;
}

void GameObject::destroy()
{
	if (parent){
		parent->deleteChild(this);
	}
}

void GameObject::deleteChild(GameObject *par_child_destroy)
{
	if (par_child_destroy)
	{	
		GameObject *go = nullptr;
		auto index = 0;
		for (auto child : childs_list){
			if (child == par_child_destroy){
				//go = child;
				childs_list.erase(childs_list.begin() + index);
				++index;
			}
		}
		delete par_child_destroy;
		
	}
}

glm::vec3 GameObject::getPosition()	const {
	return parent != nullptr ? (position + parent->getPosition()) : position;
}
glm::vec3 GameObject::getScale()	const { 
	return parent != nullptr ? (scale * parent->getScale()) : scale;
}
float GameObject::getRotation()		const { 	
	return parent != nullptr ? (rotation + parent->getRotation()) : rotation;
}

glm::vec2 GameObject::getSize()const{
	return glm::vec2 (obj_size.x * getScale().x, obj_size.y * getScale().y );
}

GameObject::TGameObjectList GameObject::getChildsList() const{
	return childs_list;
}