#ifndef _CCB_CCLAYERLOADER_H_
#define _CCB_CCLAYERLOADER_H_

//#include "CCNodeLoader.h"
//#include "extensions/CCBReader/CCNodeLoader.h"


NS_CC_EXT_BEGIN

/* Forward declaration. */
class CCBReader;

class BaseLayerLoader : public NodeLoader {
    public:
        virtual ~BaseLayerLoader() {};
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BaseLayerLoader, loader);

    protected:
        CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Layer);

        virtual void onHandlePropTypeCheck(Node * pNode, Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
};

NS_CC_EXT_END

#endif
