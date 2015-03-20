<?php
/**
 * @file
 */

/**
 * class
 */
class CompanyTermInfo {
  public $tid;
  public $term = NULL;
  
  /**
   * @parameter is tid
   */
  function __construct($tid){
    $this->tid = $tid;
    
    if (is_numeric($tid)) {
        $term = taxonomy_term_load($tid);
      if ($term) {
        $this->term = $term;
      }
    }
  }
  
  /**
   * @return Term company Name
   */
  public function companyName() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if ($this->term) {
      $output = $this->term;
    }
    return $output;
  }
  
  /**
   * @return Company Bank Name
   */
  public function companyBankName() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_bank_name['und'][0]['safe_value'])) {
      $output = $this->term->field_company_bank_name['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /**
   * @return Company Account Number
   */
  public function companyAccountNumber() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_account_number['und'][0]['safe_value'])) {
      $output = $this->term->field_company_account_number['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /**
   * @return Company Address
   */
  public function companyAddress() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_address['und'][0]['safe_value'])) {
      $output = $this->term->field_company_address['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /**
   * @return Company Contacts
   */
  public function companyContacts() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_contacts['und'][0]['safe_value'])) {
      $output = $this->term->field_company_contacts['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /**
   * @return Company Phone
   */
  public function companyPhone() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_phone['und'][0]['safe_value'])) {
      $output = $this->term->field_company_phone['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /**
   * @return Company Logo Uri
   */
  public function companyLogoUri() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_logo['und'][0]['uri'])) {
      $output = $this->term->field_company_logo['und'][0]['uri'];
    }
    return $output;
  }
  /**
   * @return Company Logo Image
   *
   * use theme_image() to generate image
   */
  public function companyLogoImage() {
    if (!$this->term) {
      return NULL;
    }
    $variables = NULL;
    $image_uri = $this->companyLogoUri();
    if ($image_uri) {
      $variables = array(
        'path' => $image_uri, 
        'alt' => 'Company Logo',
        'title' => 'Company Logo',
        'width' => '50%',
        'height' => '50%',
        'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
      );
    }
    return $variables;
  }
  
  /**
   * @return Company Stamp Uri
   */
  public function companyStampUri() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_company_stamp['und'][0]['uri'])) {
      $output = $this->term->field_company_stamp['und'][0]['uri'];
    }
    return $output;
  }
  /**
   * @return Company Logo Stamp
   *
   * use theme_image() to generate image
   */
  public function companyLogoStamp() {
    if (!$this->term) {
      return NULL;
    }
    $variables = NULL;
    $image_uri = $this->companyStampUri();
    if ($image_uri) {
      $variables = array(
        'path' => $image_uri, 
        'alt' => 'Company Stamp',
        'title' => 'Company Stamp',
        'width' => '50%',
        'height' => '50%',
        'attributes' => array('class' => 'some-img', 'id' => 'my-img'),
      );
    }
    return $variables;
  }



}
