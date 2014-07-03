<blockquote class="twitter-tweet">
  <p>
    <?php print $data->text; ?>
  </p>&mdash; <?php print $data->user->name; ?> (@<?php print $data->user->screen_name; ?>)
  <a href="<?php print $data->status_url; ?>">
    <?php print format_date(strtotime($data->created_at)); ?>
  </a>
</blockquote>
<script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>
