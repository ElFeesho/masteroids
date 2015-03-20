//
// Created by Christopher Sawczuk on 20/03/2015.
//

#ifndef _MASTEROIDS_RESOURCEMANAGER_H_
#define _MASTEROIDS_RESOURCEMANAGER_H_

class Font;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Font *boldFont();
	Font *regularFont();

private:
	Font *_boldFont;
	Font *_regularFont;

};


#endif //_MASTEROIDS_RESOURCEMANAGER_H_
