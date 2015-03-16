<?php
/**
 * @file
 * edit term
 */

/**
 * callback from hook_menu()
 */
function otherterm_edit_term($tid = NULL) {
  if (empty($tid) || !is_numeric($tid)) {
    return t('You have to select one of term type');
  }

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');

  $form_id = 'taxonomy_form_term';
  $term = taxonomy_term_load($tid);

  if (!$term) {
    return t('Please select right term number');
  }

  $title = t('Edit Term') . ' -- ';
  $vocabulary = taxonomy_vocabulary_load($term->vid);
  if ($vocabulary) {
    $title .= $vocabulary->name;
  }
  drupal_set_title($title);

  $form = drupal_get_form($form_id, $term);

  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['description']['#access'] = FALSE;
    $form['relations']['#attributes']['class'][] = 'element-hidden';
    $form['path']['#access'] = FALSE;
    $form['path']['alias']['#access'] = FALSE;
    $form['xmlsitemap']['#access'] = FALSE;
  }

  $output = drupal_render($form);

  return $output;
}
