<?php

/**
 *
 */
function sir_trevor_tweet() {
  $id = $_GET['tweet_id'];
  module_load_include('php', 'twitter', 'twitter.lib');
  $key = variable_get('twitter_consumer_key', '');
  $secret = variable_get('twitter_consumer_secret', '');
  $twitter = new Twitter($key, $secret);
  $token = $twitter->get_request_token();
  $tweet = $twitter->call('statuses/show', array('id' => $id), 'GET');
  drupal_json_output($tweet);
}

/**
 * Image upload handler.
 */
function sir_trevor_image() {
  $image = $_POST['attachment'];
  $filename = variable_get('sir_trevor_image_upload', '') .'/'. $image['uid'] . '-' . $image['name'];
  file_prepare_directory(variable_get('sir_trevor_image_upload', ''), FILE_CREATE_DIRECTORY);
  file_unmanaged_move($_FILES['attachment']['tmp_name']['file'], $filename);
  drupal_json_output(array(
    'file' => array(
      'url' => file_create_url($filename)
      )
    )
  );
}

/**
 * Administration form.
 */
function sir_trevor_admin_form() {
  $form = array();

  $form['sir_trevor_image_upload'] = array(
    '#type' => 'textfield',
    '#title' => t('Location for image uploads'),
    '#default_value' => variable_get('sir_trevor_image_upload', ''),
  );

  return system_settings_form($form);
}
