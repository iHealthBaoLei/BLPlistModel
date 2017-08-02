//
//  MyTableViewController.m
//  Demo
//
//  Created by Lei Bao on 2017/8/2.
//  Copyright © 2017年 iHealthlabs. All rights reserved.
//

#import "MyTableViewController.h"
#import "Fruit.h"
#import "BLPlistModelManager.h"

@interface MyTableViewController ()

@property (strong, nonatomic) NSMutableArray <Fruit *> *array;

@end

@implementation MyTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    [self.tableView registerClass:[UITableViewCell class] forCellReuseIdentifier:@"1234"];
    self.array = [NSMutableArray new];
    [self refreshDataSource];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addButtonDidPressed:(id)sender {
    UIAlertController *ac = [UIAlertController alertControllerWithTitle:@"Input fruit name" message:@"" preferredStyle:UIAlertControllerStyleAlert];
    [ac addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
        
    }];
    __weak typeof(self) weakSelf = self;
    UIAlertAction *action = [UIAlertAction actionWithTitle:@"Save" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        UITextField *myTextField = ac.textFields.firstObject;
        if (myTextField.text.length > 0) {
            Fruit *obj = [Fruit new];
            obj.name = myTextField.text;
            obj.identifier = myTextField.text;
            obj.ts = [NSDate date];
            [obj savePlistWithCompletion:^(BOOL successful) {
                NSLog(@"🌺");
                [weakSelf refreshDataSource];
                [weakSelf.tableView reloadData];
            }];
        }
        
    }];
    [ac addAction:action];
    [self presentViewController:ac animated:NO completion:nil];
}

- (void)refreshDataSource{
    [self.array removeAllObjects];
    [self.array addObjectsFromArray:[BLPlistModelManager getAllInstanceFromPlistWithClassName:NSStringFromClass([Fruit class])]];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.array.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"1234" forIndexPath:indexPath];
    cell.textLabel.text = self.array[indexPath.row].name;
    return cell;
}

// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}

// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        Fruit *obj = self.array[indexPath.row];
        __weak typeof(self) weakSelf = self;
        [obj removePlistWithCompletion:^(BOOL successful) {
            [weakSelf.array removeObject:obj];
            [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
        }];
        
        
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}


@end
