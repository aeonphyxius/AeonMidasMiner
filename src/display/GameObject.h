/****************************************************************************
Copyright (c) 2016 Alejandro Santiago Varela

http://www.aeonphyxius.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef MIDAS_GAMEOBJECT_H
#define MIDAS_GAMEOBJECT_H
#include <glm/glm.hpp>
#include <vector>
#include <memory>
/**
* Base class for all World's GameObjects
*
* This class provides the basic information common to all gameobjects in our game
*
*/
class GameObject {

public:

	typedef std::vector<GameObject*> TGameObjectList;

	GameObject();
	GameObject(bool par_isvisible, glm::vec3 par_position, float par_rotation, glm::vec3 par_scale);
	virtual ~GameObject();

	virtual void	addChild(GameObject* child);
	void			removeChild(GameObject* child);
	virtual void	destroy();
	virtual void	deleteChild(GameObject *child);
	virtual void	onUpdate() = 0;
	

	// default getters
	virtual bool isVisible()						const { return isvisible; }	
	virtual glm::vec3 getPosition()					const;
	virtual glm::vec3 getScale()					const;
	virtual glm::vec2 getSize()						const;
	virtual float getRotation()						const;
	virtual TGameObjectList getChildsList()			const;
	virtual bool isPointInside(const glm::vec2 *par_point) const;
	
	// default setters
	virtual void setIsVisible	(const bool par_isvisible)		{ isvisible = par_isvisible; }
	virtual void setPosition	(const glm::vec3 par_position)	{ position = par_position; }
	virtual void setRotation	(const bool par_rotation)		{ rotation = par_rotation; }
	virtual void setScale		(const glm::vec3 par_scale)		{ scale	   = par_scale; }
	virtual void setSize		(const glm::vec2 par_size)		{ obj_size = par_size; }
	
protected:
	bool							isvisible;		/* is it this object visible*/
	glm::vec3						position;		/* local position (relative to its parent) */
	glm::vec3						scale;			/* local object's scale*/
	glm::vec2						obj_size;		/* object size (depending on texture or text sizes) */
	float							rotation;		/* objects local rotation */
	GameObject						*parent;		/* its parent (null by default)*/
	TGameObjectList					childs_list;	/* childs list */

};

#endif /* defined( MIDAS_GAMEOBJECT_H )*/