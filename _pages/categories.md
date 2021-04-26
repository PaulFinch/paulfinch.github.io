---
layout: page
title: Categories
permalink: /categories/
---
<div class="archive-head">
{% for category in site.categories %}
  <div class="container">
    {% capture category_name %}{{ category | first }}{% endcapture %}
    <h1 class="archive-title"><span>[+] {{ category_name }}</span></h1>
    {% for post in site.categories[category_name] %}
        {% include article-content.html %}
    {% endfor %}
  </div>
{% endfor %}
</div>