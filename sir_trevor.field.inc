<?php

/**
 * Implements hook_field_info().
 */
function sir_trevor_field_info() {
  return array(
    'sir_trevor' => array(
      'label' => t('Sir Trevor Text Editor'),
      'description' => t('This field stores sir trevor JSON output.'),
      'default_widget' => 'sir_trevor',
      'default_formatter' => 'sir_trevor',
    ),
  );
}

/**
 * Implements hook_field_widget_info().
 */
function sir_trevor_field_widget_info() {
  return array(
    'sir_trevor' => array(
      'label' => t('Sir Trevor'),
      'field types' => array('sir_trevor'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_DEFAULT,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_settings_form().
 */
function sir_trevor_field_settings_form($field, $instance, $has_data) {
  $settings = $field['settings'];
  $blocks = array();
  foreach(module_invoke_all('sir_trevor_block_info') as $block_name => $block) {
    $blocks[$block_name] = $block['name'];
  }

  $form['sir_trevor_blocks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Available blocks'),
    '#default_value' => (isset($settings['sir_trevor_blocks'])) ? $settings['sir_trevor_blocks'] : array(),
    '#required' => TRUE,
    '#options' => $blocks,
    '#description' => t('The available blocks that people can add to this field.'),
  );

  $form['sir_trevor_default_block'] = array(
    '#type' => 'radios',
    '#title' => t('Default block'),
    '#default_value' => (isset($settings['sir_trevor_default_block'])) ? $settings['sir_trevor_default_block'] : 0,
    '#required' => TRUE,
    '#options' => $blocks,
    '#description' => t('The default block type created.'),
  );

  return $form;
}

/**
 * Implements hook_field_formatter_info().
 */
function sir_trevor_field_formatter_info() {
  return array(
    'sir_trevor' => array(
      'label' => t('Sir Trevor'),
      'field types' => array('sir_trevor'),
    ),
  );
}

/**
 * Implements hook_field_formatter_view().
 */
function sir_trevor_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  if($display['type'] != 'sir_trevor') {
    return $element;
  }
  $blocks = module_invoke_all('sir_trevor_block_info');
  $sir_trevor_blocks = array();
  foreach($blocks as $block_name => $block) {
    $sir_trevor_blocks[$block['type']] = $block_name;
  }
  $settings = $field['settings'];
  foreach($items as $delta => $item) {
    $json = json_decode($item['json']);
    $ouptut = array();
    foreach($json->data as $data) {
      $theme_name = 'sir_trevor_' . $sir_trevor_blocks[$data->type];
      if(isset($blocks[$sir_trevor_blocks[$data->type]]['theme'])) {
        $theme_name = $blocks[$sir_trevor_blocks[$data->type]]['theme'];
      }
      $output[] = theme($theme_name, array('settings' => $field['settings'], 'data' => $data->data));
    }
    $element[$delta] = array('#markup' => implode("\n", $output));
  }
  return $element;
}

/**
 * Implements hook_field_widget_form().
 */
function sir_trevor_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  module_invoke_all('sir_trevor_loading');
  $blocks = module_invoke_all('sir_trevor_block_info');
  $settings = array('blocks' => array(),
    'default' => $blocks[$field['settings']['sir_trevor_default_block']]['sir_trevor_name']);
  foreach($field['settings']['sir_trevor_blocks'] as $block => $enabled) {
    if($enabled) {
      $settings['blocks'][] = $blocks[$block]['sir_trevor_name'];
    }
  }
  drupal_add_js(array('sir_trevor' => $settings), 'setting');

  $main_widget = $element + array(
    '#type' => 'textarea',
    '#default_value' => isset($items[$delta]['json']) ? $items[$delta]['json'] : NULL,
    '#attributes' => array('class' => array('sir-trevor-textarea')),
    '#resizable' => FALSE
  );
  $element['json'] = $main_widget;
  return $element;
 }

/**
 * Implements hook_field_is_empty().
 */
function sir_trevor_field_is_empty($item, $field) {
  return !$item['json'] || $item['json'] == '';
}
