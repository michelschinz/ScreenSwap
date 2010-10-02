#include <CoreFoundation/CoreFoundation.h>
#include <ApplicationServices/ApplicationServices.h>

int main (int argc, const char * argv[]) {
  uint32_t displayCount;
  CGGetActiveDisplayList(0, NULL, &displayCount);

  if (displayCount != 2) {
    fprintf(stderr, "Error: expected exactly 2 displays, %d found\n", displayCount);
    exit(1);
  }
  
  CGDirectDisplayID activeDisplays[displayCount];
  CGGetActiveDisplayList(displayCount, activeDisplays, &displayCount);

  const int32_t xTranslation = -CGRectGetMinX(CGDisplayBounds(activeDisplays[1]));
  
  CGDisplayConfigRef config;
  CGBeginDisplayConfiguration(&config);
  CGConfigureDisplayFadeEffect(config, 0.2, 0.2, 0, 0, 0);
  for (int i = 0; i < displayCount; ++i) {
    CGDirectDisplayID display = activeDisplays[i];
    CGRect displayBounds = CGDisplayBounds(display);
    CGConfigureDisplayOrigin(config, display, CGRectGetMinX(displayBounds) + xTranslation, CGRectGetMinY(displayBounds));
  }  
  CGCompleteDisplayConfiguration(config, kCGConfigurePermanently);
  
  return 0;
}
