<?php
/**
 * @file for Set Home page direct
 */
/**
 * function callback from hook_menu()
 */
function othersetting_home_page_callback() {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }
  // check roles to direct different page
  if(user_is_anonymous()) {
    drupal_goto('search-repair');
  }
  else if (user_is_logged_in()) {
    $allowed_value = 'keyclient';
    if (in_array($allowed_value, array_values($account->roles))) {
      if(isset($account->name)) {
        $term_array = taxonomy_get_term_by_name($account->name, 'client');
        $term = current($term_array);
        if(isset($term->tid)) {
          drupal_goto('repair-key/' . $term->tid);
        }
      }
      drupal_goto('search-repair');
    } 
    else {
      drupal_goto('repair-list');
    }
  }
  
}