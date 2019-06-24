#ifndef VITAMATERIALKIT_CARDSSAMPLE_HH
#define VITAMATERIALKIT_CARDSSAMPLE_HH


#include "../../kit/core/View.hh"

class CardsSample : public View {
private:
    CardPrePrimaryTitle cardPrePrimaryTitle;
    CardPreSummary cardPreSummary;
    ZoneEvent back;

public:
    CardsSample(const std::string &name);

    void contents() override;

    void mounted() override;

    void controls() override;

    void beforeEnter() override;
};


#endif //VITAMATERIALKIT_CARDSSAMPLE_HH
