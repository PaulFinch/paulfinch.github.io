---
title: PaulFinch
layout: default
description: Paperstreet & Co
---
paulfinch.github.io

<div class="container">
	<div class="row">
		<div class="col col-12">
			{% if site.posts.size > 0 %}
				<h4 class="lates-title">Derniers Posts</h4>
			{% endif %}
		</div>
	</div>
	<div class="row">
	{% if site.posts.size > 0 %}
		{% for post in paginator.posts %}
			{% include article-content.html %}
		{% endfor %}
	{% endif %}
	</div>
</div>

{% include pagination.html %}
