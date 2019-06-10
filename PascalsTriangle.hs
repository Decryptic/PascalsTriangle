-- an original implementation of Pascal's triangle
-- by Gage Swenson (gageswenson@gmail.com)
--
-- sponsored by ItLit
-- https://itlit.io
-- 

module Main where

import System.Environment (getArgs)

triangle :: Int -> [[Int]]
triangle 0 = [[1]]
triangle 1 = triangle 0 ++ [[1, 1]]
triangle n = 
    let top = triangle (n-1)
    in top ++ [makeRow 0 (last top)]
    where
    makeRow :: Int -> [Int] -> [Int]
    makeRow x rowAbove
        | x == 0    = 1 : makeRow (x+1) rowAbove
        | x == n    = [1]
        | otherwise = (rowAbove!!x + rowAbove!!(x-1)) : makeRow (x+1) rowAbove
        

showTriangle :: [[Int]] -> String
showTriangle [] = ""
showTriangle (r:rs) = replicate (length rs) '\t' ++ tabOut r ++ "\n" ++ showTriangle rs
    where
    tabOut :: [Int] -> String
    tabOut [c] = show c
    tabOut (c:cs) = show c ++ "\t\t" ++ tabOut cs

pascals :: Int -> String
pascals = showTriangle . triangle

main :: IO ()
main = do
    args <- getArgs
    case args of
        []     -> putStrLn "argc must be greater than 0"
        (x:xs) -> case isInt x of
            False -> putStrLn "argv[0] must be a positive int"
            True  -> putStr $ pascals (read x :: Int)
    where
    isInt :: String -> Bool
    isInt "" = False
    isInt [d]
        | isDigit d = True
        | otherwise = False
    isInt (d:ds)
        | isDigit d = True && isInt ds
        | otherwise = False
    isDigit :: Char -> Bool
    isDigit = (`elem` "1234567890")
