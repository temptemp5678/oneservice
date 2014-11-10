(function ($) {
  Drupal.behaviors.zencharts = {
    attach: function (context, settings) {
      /**
       *
       */
      jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').on('click', function() {
         // console.log(jQuery(this.checked)[0]);
         // console.log(jQuery(this.val());
         checkSelectedLength();
      });

      /**
       * check length for Checkbox,
       * if "length" is 0 return warning text
       * if "length" is more than 0, call function to return HTML table output
       */
      function checkSelectedLength() {
        var rowContent = [];
        var nidSelected = [];
        jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').each(function () {
           if (this.checked) {
             rowContent.push(jQuery(this).val());
             nidSelected.push(jQuery(this).attr("nid"));
           }
        });
        
        var output = '';
        if (rowContent.length > 0 ) {
          jQuery.each(rowContent, function( index, value ) {
            output += '<p>' + value + '</p>';
          });
        }
        else {
          output = '<p>No selected Device</p>';
        }
        // insert HTML
        jQuery('.quote-row-output-html').html(output);
        
        /** - - - - - - - - - - - - - - - - - - - -  */
        // Firstly, empty all value for NID field
        jQuery('#quotetype-add-quote-form .quotation-js-insert-repair-nid input').each(function () {
          jQuery(this).val('');
        });
        if (nidSelected.length > 0) {
          console.log(nidSelected.length);
          jQuery.each(nidSelected, function( index, value ) {
            // jQuery('#quotetype-add-quote-form .quotation-js-insert-repair-nid input:nth-child(3)').val(6);
            jQuery('#quotetype-add-quote-form .quotation-js-insert-repair-nid input').eq(index).val(value);
          });
          console.log(nidSelected);
        }
      }
      
      /** - - - - - - - - - - - - - - - - - - - -  */


    // --- end for attach: function()
    }
  };
})(jQuery);