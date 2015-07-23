//
// Created by Christopher Sawczuk on 20/03/2015.
//

#ifndef _MASTEROIDS_RESOURCEMANAGER_H_
#define _MASTEROIDS_RESOURCEMANAGER_H_

class Font;

class ResourceManager
{
public:
    ResourceManager(const Font &boldFont, const Font &regularFont);
    ResourceManager(ResourceManager &&) = default;
	~ResourceManager();

    const Font &boldFont() const;
    const Font &regularFont() const;

private:
    const Font &_regularFont;
    const Font &_boldFont;

};


#endif //_MASTEROIDS_RESOURCEMANAGER_H_
