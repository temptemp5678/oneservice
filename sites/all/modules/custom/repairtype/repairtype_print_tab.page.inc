<?php
/**
 * @file
 */

/**
 * callback from hook_menu()
 * Embed Views to output content
 */
function repairtype_print_tab_page($nid = NULL) {
  if (empty($nid) || !is_numeric($nid)) {
    return t('You have to select one of page');
  }

  $node = node_load($nid);
  if (!$node) {
    return t('Please select right repair number');
  }
  if ($node->type != 'repair') {
    return t('Please select right repair number');
  }
  
  $RepairInfo = new RepairInfo($nid);
  $quote_nid = $RepairInfo->quoteNid();
  
  // page output
  $output = '';
  if ($quote_nid) {
    $QuoteInfo = new QuoteInfo($quote_nid);
    $company_term_tid = $QuoteInfo->companyNameTid();
    
    $CompanyTermInfo = new CompanyTermInfo($company_term_tid);
    $company_logo_variables = $CompanyTermInfo->companyLogoImageVariables();
    $company_logo_image = theme('image', $company_logo_variables); 

    $output .= '<div class="visible-print">' . $company_logo_image . '</div>';
  }

  $output .= views_embed_view('repair_print_table', 'default', $nid);

  if ($quote_nid) {
    $output .= '<div class="repair-print-page-company-info-wrapper margin-bottom-12 text-center">';
      $output .= '<div class="repair-print-page-company-info-item">';
        $output .= $CompanyTermInfo->companyName();
      $output .= '</div>';
      $output .= '<div class="repair-print-page-company-info-item">';
        $output .= $CompanyTermInfo->companyAddress();
      $output .= '</div>';
      $output .= '<div class="repair-print-page-company-info-item">';
        $output .= $CompanyTermInfo->companyPhone();
      $output .= '</div>';
    $output .= '</div>';
    // add print button
    $output .= '<div class="btn btn-success repair-node-print-button hidden-print" type="button">' . t('Print') . '</div>';
    drupal_add_js('jQuery(document).ready(function () {
        jQuery(".repair-node-print-button").click(function(){
          window.print();
          return false;
        });
      });',
      'inline'
    );
  }
  else {
    $output .= '<div class="repair-print-page-company-info-item">';
      $output .= t('The page can\'t find Quote item');
    $output .= '</div>';
  }
  
  return $output;
}