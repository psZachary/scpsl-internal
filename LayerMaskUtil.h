#pragma once
#include <vector>

namespace LayerMaskUtil {
	std::vector<bool> GetActiveLayers(int _this, int layerMask) {
		static std::vector<bool> tmp;
        static wchar_t buf[5000];
		tmp.clear();

        for (int i = 0; i < 32; i++)
        {
            auto mask = (layerMask | (1 << i));
            if (layerMask == mask)
            {
                tmp.push_back(true);
            }
            else {
                tmp.push_back(false);
            }
        }

        return tmp;
	}
}