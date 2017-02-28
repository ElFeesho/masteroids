#import "resources.h"

#import <Foundation/Foundation.h>

std::string Resources::regularFontLocation() {
	NSBundle *mainBundle = [NSBundle mainBundle];

	NSString *path = [mainBundle pathForResource:@"regularfont" ofType:@"ttf"];

	return std::string([path UTF8String]);
}

std::string Resources::boldFontLocation() {
	NSBundle *mainBundle = [NSBundle mainBundle];	

	NSString *path = [mainBundle pathForResource:@"boldfont" ofType:@"ttf"];
	
	return std::string([path UTF8String]);
}