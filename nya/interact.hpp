#pragma once

#include<bits/stdc++.h>

namespace nya {

template <class ty>
class	interact {
	std::weak_ptr<interact> pre_;
	std::shared_ptr<interact> nxt_;

public:
	std::unique_ptr<ty> val_;

	template <class...argz>
	interact(argz&&...arg)
		: val_(std::make_unique<ty>(std::forward<argz>(arg)...)) {}

	~interact(void) noexcept {}

	template <class ref_ty, class...argz>
	void	touch(const ref_ty &ref_this, argz&&...arg)
		pre(&*ref_this == this) {
		std::shared_ptr<interact<ty>> x = std::make_shared<interact<ty>>(std::forward<argz>(arg)...);
		x->pre_ = ref_this;
		x->nxt_ = std::move(nxt_);

		if (x->nxt_)
			x->nxt_->pre_ = x;

		nxt_ = x;
	}

	void	rm(void) noexcept
		pre(pre_) {
		if (nxt_)
			nxt_->pre_ = pre_;

		pre_->nxt_ = nxt_;
	}

	bool	has_ring(void) const noexcept
		pre(!pre_) {
		std::map<std::weak_ptr<interact<ty>>, bool> yani;

		for (std::weak_ptr<interact<ty>> x = nxt_; x; x = x->nxt_) {
			if (yani[x])
				return 1;

			yani[x] = 1;
		}

		return 0;
	}

	std::vector<std::weak_ptr<interact<ty>>> cast_vector(void) const noexcept
		pre(!pre_ && !has_ring()) {
		std::vector<std::weak_ptr<interact<ty>>> yaku;

		for (std::weak_ptr<interact<ty>> x = nxt_; x; x = x->nxt_)
			yaku.emplace_back(x);

		return yaku;
	}
};

}
