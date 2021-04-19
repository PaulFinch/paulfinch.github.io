---
title: PaulFinch
layout: default
description: Paperstreet & Co
---
paulfinch.github.io

<ul>
  {% for post in site.posts %}
    <li>
      <a href="{{ post.url }}">{{ post.title }}</a>
    </li>
  {% endfor %}
</ul>

<div class="container">
	<div class="row">
	{% if site.posts.size > 0 %}
		{% for post in site.posts %}
			{% include article-content.html %}
		{% endfor %}
	{% endif %}
	</div>
</div>

{% include pagination.html %}
