<?php if($data->source == 'youtube'): ?>
  <iframe class="sir-trevor-video" width="853" height="480" src="//www.youtube.com/embed/<?php print $data->remote_id; ?>" frameborder="0" allowfullscreen></iframe>
<?php endif; ?>
